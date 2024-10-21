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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "common/lang/defer.h"

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      Expression *condition, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  if(condition == nullptr){
    return rc;
  }

  auto check_condition_expr = [&db, &default_table, &tables](Expression *expr) {
    if (expr->type() == ExprType::COMPARISON) {
      ComparisonExpr* cmp_expr = static_cast<ComparisonExpr*>(expr);
      CompOp comp = cmp_expr->comp();
      if (comp < EQUAL_TO || comp >= NO_OP) {
        LOG_WARN("invalid compare operator : %d", comp);
        return RC::INVALID_ARGUMENT;
      }
    }else if(expr->type() == ExprType::CONJUNCTION){
      ConjunctionExpr* conj_expr = static_cast<ConjunctionExpr*>(expr);
      if(conj_expr->conjunction_type() != ConjunctionExpr::Type::AND && conj_expr->conjunction_type() != ConjunctionExpr::Type::OR){
        LOG_WARN("invalid conjunction operator");
        return RC::INVALID_ARGUMENT;
      }
    }else if(expr->type() == ExprType::NULLTYPE){
      return RC::SUCCESS;
    }else if(expr->type() == ExprType::VALUE){
      return RC::SUCCESS;
    }else if(expr->type() == ExprType::FIELD){
      //检查字段是否存在
      FieldExpr* field_expr = static_cast<FieldExpr*>(expr);

      const char *table_name = strlen(field_expr->table_name()) == 0 ? default_table->name() : field_expr->table_name();
      if(table_name == nullptr){
        LOG_WARN("no table name");
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      field_expr->set_table_name(table_name);
      const char* field_name = field_expr->field_name();
      if(field_name == nullptr){
        LOG_WARN("no field name");
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }
      Table* table = db->find_table(table_name);
      if(table == nullptr){
        LOG_WARN("no such table");
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      const FieldMeta* field = table->table_meta().field(field_name);
      if(field == nullptr){
        LOG_WARN("no such field in table");
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }
      field_expr->set_field(Field(table, field));

    }else if(expr->type() == ExprType::SUBQUERY){
      SubQueryExpr* subquery_expr = static_cast<SubQueryExpr*>(expr);
      //生成子查询的select stmt
      return subquery_expr->generate_select_stmt(db, *tables);
    }
    return RC::SUCCESS;
  };
  rc = condition->traverse_check(check_condition_expr);
  if (RC::SUCCESS != rc) {
    return rc;
  }

  FilterStmt *tmp_stmt = new FilterStmt();
  tmp_stmt->condition_expr_ = std::unique_ptr<Expression>(condition);
  stmt = tmp_stmt;
  return rc;
}