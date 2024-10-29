#include "sql/stmt/select_stmt.h"
#include "sql/operator/view_scan_physical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "storage/table/view.h"
#include "event/sql_debug.h"
#include "common/log/log.h"
#include "sql/expr/expression_tuple.h"

using namespace std;

/* 
 *  open时需要从View中的SelectSqlNode创建子查询
 */
RC ViewScanPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;

  Stmt *select_stmt;
  SelectSqlNode select_sql;
  select_sql.deep_copy(view_->get_select_sql());
  rc = SelectStmt::create(view_->get_db(), select_sql, select_stmt);
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to create select_stmt when view_scan open, rc=%s", strrc(rc));
    return rc;
  }

  std::unique_ptr<LogicalOperator> logical_oper;
  LogicalPlanGenerator  logical_plan_generator;
  rc = logical_plan_generator.create(select_stmt, logical_oper);
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to create select_logical_oper when view_scan open, rc=%s", strrc(rc));
    return rc;
  }

  PhysicalPlanGenerator physical_plan_generator;
  LOG_INFO("logical_oper type: %d", logical_oper->type());
  rc = physical_plan_generator.create(*logical_oper, physical_oper_);
  LOG_INFO("physical_oper_ type: %d", physical_oper_->type());
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to create select_physical_oper when view_scan open, rc=%s", strrc(rc));
    return rc;
  }

  rc = physical_oper_->open(trx);
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to open select_physical_oper when view_scan open, rc=%s", strrc(rc));
    return rc;
  }

  tuple_.set_schema(view_);
  record_size_ = view_->table_meta().record_size();
  record_data_ = (char*)malloc(sizeof(char) * (record_size_));
  if (nullptr == record_data_) {
    LOG_ERROR("failed to alocate memory for record data");
    return RC::INTERNAL;
  }
  view_record_.set_data(record_data_);

  trx_ = trx;
  return rc;
}

RC ViewScanPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;

  LOG_INFO("view scan next");

  bool filter_result = false;
  int field_num = view_->table_meta().field_num();
  int sys_field_num = view_->table_meta().sys_field_num();
  int null_offset = view_->table_meta().null_field()->offset();
  tuple_.clear_map();

  while (RC::SUCCESS == (rc = physical_oper_->next())) {
    Tuple *tuple = physical_oper_->current_tuple();

    // 需要将不知道是什么类型的Tuple，处理成RowTuple，这里需要重新构造Record，但是需要保留RID
    memset(record_data_, 0, record_size_);
    common::Bitmap record_bitmap(record_data_ + null_offset, field_num);
    for (size_t col_idx = 0; col_idx < tuple->cell_num(); col_idx++) {
      Value view_col_val;
      const FieldMeta *table_field_meta = view_->table_meta().field(col_idx + sys_field_num);
      // TODO: TEXT类型期望只拿到位置信息，不拿原始字符串
      tuple->cell_at(col_idx, view_col_val);
      size_t copy_len = std::min(view_col_val.length(), table_field_meta->len());
      if (view_col_val.is_null()) {
        record_bitmap.set_bit(col_idx + sys_field_num);
      } else {
        memcpy(record_data_ + table_field_meta->offset(), view_col_val.data(), copy_len);
      }
    }
    tuple_.set_record(&view_record_);

    const Tuple *child_tuple = static_cast<ExpressionTuple<std::unique_ptr<Expression>>*>(tuple)->get_child_tuple();
    for (int i = 0; i < child_tuple->get_tuple_size(); i++) {
      const BaseTable *table;
      RID rid;
      rc = child_tuple->get_tuple_rid(i, table, rid);
      if (RC::SUCCESS != rc) {
        LOG_ERROR("failed to get table_rid [%d] from tuple, tuple_size=%d", i, child_tuple->get_tuple_size());
        return rc;
      }
      rc = tuple_.add_table_rid_into_map(table, rid);
      if (RC::SUCCESS != rc) {
        LOG_ERROR("failed to add table_rid into rowtuple, table:%s, rid:%ld-%ld", table->name(), rid.page_num, rid.slot_num);
        return rc;
      }
    }

    rc = filter(tuple_, filter_result);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (filter_result) {
      sql_debug("get a tuple: %s", tuple_.to_string().c_str());
      break;
    } else {
      sql_debug("a tuple is filtered: %s", tuple_.to_string().c_str());
      rc = RC::RECORD_EOF;
    }
  }
  return rc;
}

RC ViewScanPhysicalOperator::close()
{
  return physical_oper_->close();
}

Tuple *ViewScanPhysicalOperator::current_tuple()
{
  return &tuple_;
}

string ViewScanPhysicalOperator::param() const
{
  return view_->name();
}

void ViewScanPhysicalOperator::set_predicates(vector<unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC ViewScanPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC rc = RC::SUCCESS;
  Value value;
  for (unique_ptr<Expression> &expr : predicates_) {
    rc = expr->get_value(tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}
