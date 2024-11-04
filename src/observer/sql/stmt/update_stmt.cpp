/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by liuxin on 2024/10/14.
//

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/stmt/filter_stmt.h"

UpdateStmt::UpdateStmt(
    BaseTable *table, std::vector<Expression *> expressions, std::vector<FieldMeta> fields, FilterStmt *filter_stmt)
    : table_(table), expressions_(expressions), fields_(fields), filter_stmt_(filter_stmt)
{}

UpdateStmt::~UpdateStmt()
{
  if (filter_stmt_ != nullptr) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt)
{
  const char *table_name = update_sql.relation_name.c_str();
  if (db == nullptr || table_name == nullptr) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  BaseTable *table = db->find_base_table(table_name);
  if (table == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  auto check_field = [&db](Expression *expr) {
    if (expr->type() == ExprType::SUBQUERY) {
      SubQueryExpr *subquery_expr = static_cast<SubQueryExpr *>(expr);
      return subquery_expr->generate_select_stmt(db, {});
    }
    return RC::SUCCESS;
  };

  std::vector<Expression *> values;
  std::vector<FieldMeta>    fields;
  const TableMeta          &table_meta = table->table_meta();

  for (size_t i = 0; i < update_sql.attribute_names.size(); i++) {
    FieldMeta *update_field = const_cast<FieldMeta *>(table_meta.field(update_sql.attribute_names[i].c_str()));
    bool       valid        = false;
    if (update_field == nullptr) {
      LOG_WARN("no such field. table_name=%s, field_name=%s", table_name, update_sql.attribute_names[i].c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    if (update_sql.expressions[i]->type() == ExprType::VALUE) {
      const Value &val = static_cast<const ValueExpr *>(update_sql.expressions[i])->get_value();
      if (val.is_null() && !update_field->nullable()){
        valid = false;
      } else if (AttrType::VECTORS == update_field->type() && AttrType::CHARS == val.attr_type()) {
        int dim = 0;
        string str = val.get_string();
        for(int j = 0; j < val.length(); j++){
          if(str[j] == ','){
            dim++;
          }
        }
        dim++;
        if(dim > MAX_VECTOR_DIM){
          LOG_WARN("vector dimension:%d, over max_dimension 16000", dim);
          return RC::INVALID_ARGUMENT;
        }
        LOG_INFO("str:%s, dim:%d", str.c_str(), dim);
        Value vec_value(str.c_str(), val.length());
        Expression *vec_expr = new ValueExpr(vec_value);
        fields.emplace_back(*update_field);
        values.emplace_back(vec_expr);
        valid = true;
        continue;
      }else if (update_field->type() == val.attr_type() || (val.is_null() && update_field->nullable())) {
        if (update_field->type() == AttrType::CHARS && update_field->len() < val.length()) {
          LOG_WARN("update chars with longer value.");
        } else {
          valid = true;
        }
      } else if (AttrType::TEXTS == update_field->type() && AttrType::CHARS == val.attr_type()) {
        if (MAX_TEXT_LENGTH < val.length()) {
          LOG_WARN("Text length:%d, over max_length 65535", val.length());
          return RC::INVALID_ARGUMENT;
        }
        valid = true;
      } else {
        valid = true;
      }
    } else {
      if (RC rc = update_sql.expressions[i]->traverse_check(check_field); RC::SUCCESS != rc) {
        return rc;
      }
      valid = true;
    }

    if (!valid) {
      LOG_WARN("update field type mismatch. table=%s", table_name);
      return RC::INVALID_ARGUMENT;
    }

    fields.emplace_back(*update_field);
    values.emplace_back(update_sql.expressions[i]);
  }

  std::unordered_map<std::string, BaseTable *> table_map;
  table_map.insert(std::pair<std::string, BaseTable *>(std::string(table_name), table));
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db, table, &table_map,{table}, update_sql.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  stmt = new UpdateStmt(table, std::move(values), std::move(fields), filter_stmt);
  return RC::SUCCESS;
}
