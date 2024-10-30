/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "sql/operator/update_physical_operator.h"
#include "storage/trx/trx.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  rc = find_target_columns();

  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to find target columns: %s", strrc(rc));
    return rc;
  }
  trx_ = trx;
  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::find_target_columns()
{
  // 如果字段检查失败 并不停止执行 只是打个标志 因为如果更新 0 行必然返回成功
  RC        rc             = RC::SUCCESS;
  const int sys_field_num  = table_->table_meta().sys_field_num();
  const int user_field_num = table_->table_meta().field_num() - sys_field_num;
  RowTuple  tp;

  for (size_t c_idx = 0; c_idx < fields_.size(); c_idx++) {
    std::string &attr_name = fields_[c_idx];

    // 先找到要更新的列，获取该列的 id、FieldMeta(offset、length、type)
    for (int i = 0; i < user_field_num; ++i) {
      const FieldMeta *field_meta = table_->table_meta().field(i + sys_field_num);
      const char      *field_name = field_meta->name();
      if (0 != strcmp(field_name, attr_name.c_str())) {
        continue;
      }

      Expression *expr = expressions_[c_idx];

      Value raw_value;

      if (expr->type() == ExprType::SUBQUERY) {
        SubQueryExpr *subquery_expr = static_cast<SubQueryExpr *>(expr);

        if (rc = subquery_expr->open(nullptr); RC::SUCCESS != rc) {
          return rc;
        }
        rc = subquery_expr->get_value(tp, raw_value);
        if (RC::RECORD_EOF == rc) {
          raw_value.set_null();
          rc = RC::SUCCESS;
        } else if (RC::SUCCESS != rc) {
          return rc;
        } else if (subquery_expr->has_more_row(tp)) {
          invalid_ = true;
          break;
        }
        subquery_expr->close();
      } else {
        if (rc = expr->get_value(tp, raw_value); RC::SUCCESS != rc) {
          return rc;
        }
      }

      if (raw_value.is_null() && field_meta->nullable()){

      } else if (raw_value.attr_type() != field_meta->type()){
        if (AttrType::TEXTS == field_meta->type() && AttrType::CHARS == raw_value.attr_type()){
        } else if (Value::cast_to(raw_value, field_meta->type(), raw_value) != RC::SUCCESS){
          LOG_WARN("failed to cast value: %s", strrc(rc));
          invalid_ = true;
          break;
        }
      }

      if (raw_value.is_null() && !field_meta->nullable()) {
        LOG_WARN("field %s is not nullable", field_name);
        invalid_ = true;
      }

      if (!invalid_) {
        raw_values_.emplace_back(raw_value);
        fields_id_.emplace_back(i + sys_field_num);
        fields_meta_.emplace_back(*field_meta);
      }
      break;
    }
  }

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    if (invalid_) {  // 子查询结果为多行
      return RC::INVALID_ARGUMENT;
    }

    Tuple *tuple = child->current_tuple();
    
    // this->current_tuple_ = tuple;

    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }
    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);

    Record &record = row_tuple->record();
    Record  new_record;

    RC rc2 = RC::SUCCESS;
    if (RC::SUCCESS != (rc2 = construct_new_record(record, new_record))) {
      if (RC::RECORD_DUPLICATE_KEY == rc2) {
        continue;
      } else {
        return rc2;
      }
    }
    LOG_INFO("update record:");
    rc = table_->update_record(record, new_record);
    LOG_INFO("update record end");
    if (rc != RC::SUCCESS) {
      // 更新失败，需要回滚之前成功的record
      LOG_WARN("failed to update record: %s", strrc(rc));

      // old_records中最后一条记录是刚才更新失败的，不需要回滚
      old_rids_.pop_back();
      old_values_.pop_back();
      new_record.set_data(nullptr);

      for (int i = old_rids_.size() - 1; i >= 0; i--) {
        Record old_record;
        Record updated_record;
        if (RC::SUCCESS != (rc2 = table_->get_record(old_rids_[i], updated_record))) {
          LOG_WARN("Failed to get record when try to rollback, rc=%s", strrc(rc2));
          break;
        } else if (RC::SUCCESS != (rc2 = construct_old_record(updated_record, old_record))) {
          LOG_WARN("Failed to construct old_record from updated one, rc=%s", strrc(rc2));
          break;
        } else if (RC::SUCCESS != (rc2 = table_->update_record(updated_record, old_record))) {
          LOG_WARN("Failed to rollback record, rc=%s", strrc(rc2));
          break;
        }
      }
      return rc;
    }
  }
  return rc;
}

RC UpdatePhysicalOperator::construct_new_record(Record &old_record, Record &new_record)
{
  RC rc = RC::SUCCESS;

  new_record.set_rid(old_record.rid());
  new_record.set_data(tmp_record_data_);
  memcpy(tmp_record_data_, old_record.data(), table_->table_meta().record_size());

  std::vector<Value> old_value;
  for (size_t c_idx = 0; c_idx < fields_.size(); c_idx++) {
    Value     *value      = &raw_values_[c_idx];
    FieldMeta &field_meta = fields_meta_[c_idx];

    // 判断 新值与旧值是否相等，缓存旧值，将新值复制到新的record里
    const FieldMeta *null_field = table_->table_meta().null_field();
    common::Bitmap   old_null_bitmap(old_record.data() + null_field->offset(), table_->table_meta().field_num());
    common::Bitmap   new_null_bitmap(tmp_record_data_ + null_field->offset(), table_->table_meta().field_num());

    // new_null_bitmap.clear_bit(fields_id_[c_idx]);
    if (value->is_null() && old_null_bitmap.get_bit(fields_id_[c_idx])) {
      old_value.emplace_back(field_meta.type(), nullptr, 0);
    } else if (value->is_null()) {
      new_null_bitmap.set_bit(fields_id_[c_idx]);
      old_value.emplace_back(field_meta.type(), old_record.data() + field_meta.offset(), field_meta.len());
    } else {
      new_null_bitmap.clear_bit(fields_id_[c_idx]);
      if (AttrType::CHARS == field_meta.type()) {
        memcpy(tmp_record_data_ + field_meta.offset(), value->data(),value->length() == field_meta.len() ? value->length() : value->length() + 1);
      } else if (AttrType::TEXTS == field_meta.type()){
        int64_t position[2];
        position[1] = value->length();
        table_->text_buffer_pool_->append_data(position[0], position[1], value->data());
        memcpy(tmp_record_data_ + field_meta.offset(), position, 2 * sizeof(int64_t));
      }else {
        memcpy(tmp_record_data_ + field_meta.offset(), value->data(), field_meta.len());
      }

      if (old_null_bitmap.get_bit(fields_id_[c_idx])) {
        old_value.emplace_back(AttrType::NULLS, nullptr, 0);
      } else {
        old_value.emplace_back(field_meta.type(), old_record.data() + field_meta.offset(), field_meta.len());
      }
    }
    // old_value.emplace_back(field_meta.type(), old_record.data() + field_meta.offset(), field_meta.len());
  }
  // 比较整行数据
  if (0 == memcmp(old_record.data(), tmp_record_data_, table_->table_meta().record_size())) {
    LOG_WARN("update old value equals new value, skip this record");
    return RC::RECORD_DUPLICATE_KEY;
  }

  old_values_.emplace_back(std::move(old_value));
  old_rids_.emplace_back(old_record.rid());
  return rc;
}

RC UpdatePhysicalOperator::construct_old_record(Record &updated_record, Record &old_record)
{
  RC rc = RC::SUCCESS;

  old_record.set_rid(updated_record.rid());
  old_record.set_data(tmp_record_data_);
  memcpy(tmp_record_data_, updated_record.data(), table_->table_meta().record_size());

  std::vector<Value> &old_value = old_values_.back();
  int                 val_idx   = 0;
  for (size_t c_idx = 0; c_idx < fields_.size(); c_idx++) {
    Value     *value      = &old_value[val_idx++];
    FieldMeta &field_meta = fields_meta_[c_idx];

    // 将旧值复制到 old_record 里
    const FieldMeta *null_field = table_->table_meta().null_field();
    common::Bitmap   old_null_bitmap(tmp_record_data_ + null_field->offset(), table_->table_meta().field_num());
    common::Bitmap updated_null_bitmap(updated_record.data() + null_field->offset(), table_->table_meta().field_num());

    if (value->is_null()) {
      old_null_bitmap.set_bit(fields_id_[c_idx]);
    } else {
      old_null_bitmap.clear_bit(fields_id_[c_idx]);
    }
    memcpy(tmp_record_data_ + field_meta.offset(), value->data(), field_meta.len());
  }

  old_rids_.pop_back();
  old_values_.pop_back();
  return rc;
}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}