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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/orderby_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
  if (nullptr != orderby_stmt_) {
    delete orderby_stmt_;
    orderby_stmt_ = nullptr;
  }
  if (nullptr != having_stmt_) {
    delete having_stmt_;
    having_stmt_ = nullptr;
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, 
  const std::unordered_map<std::string, BaseTable *> &parent_table_map)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;

  // collect tables in `from` statement
  vector<BaseTable *>                tables;
  unordered_map<string, BaseTable *> table_map = parent_table_map; //直接赋值，后面别名重复时覆盖，以当前作用域为主
  vector<JoinTables> join_tables;

  // 建立查询中涉及到的表的信息
  for (auto &relation : select_sql.relations) {
    // if(table_map.find(relation.base_relation.first) == table_map.end()){
    BaseTable *table = db->find_base_table(relation.base_relation.first.c_str());
    if (nullptr == table) {
      LOG_WARN("no such table: %s", relation.base_relation.first.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    tables.push_back(table);
    // table_alias_src_map[relation.base_relation.second] = relation.base_relation.first;
    // binder_context.set_table_alias_src(relation.base_relation.second, relation.base_relation.first);
    binder_context.add_table(relation.base_relation.first, table);
    table_map[relation.base_relation.first] = table;
    if(relation.base_relation.second.size() > 0){
      //如果有别名，也放入map中
      table_map[relation.base_relation.second] = table;
      if(!binder_context.add_table(relation.base_relation.second, table)){
        LOG_WARN("table alias %s already exists", relation.base_relation.second.c_str());
        return RC::INVALID_ARGUMENT;
      }
    }
    // }
    
    const std::vector<pair<string, string>>& join_relations = relation.join_relations;
    for (size_t j = 0; j < join_relations.size(); ++j) {
      if (table_map.find(join_relations[j].first) != table_map.end()) {
        continue;
      }
      BaseTable *table = db->find_base_table(join_relations[j].first.c_str());
      if (nullptr == table) {
        LOG_WARN("no such table: %s", join_relations[j].first.c_str());
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      tables.push_back(table);

      // table_alias_src_map[relation.base_relation.second] = relation.base_relation.first;
      // binder_context.set_table_alias_src(relation.base_relation.second, relation.base_relation.first);

      binder_context.add_table(join_relations[j].first, table);
      table_map[join_relations[j].first] = table;
      if (join_relations[j].second.size() > 0) {
        // 如果有别名，也放入map中
        binder_context.add_table(join_relations[j].second, table);
        table_map[join_relations[j].second] = table;  // 别名也当正常表放入
      }
    }
  }

  LOG_INFO("tables num : %d", tables.size());

  for (size_t i = 0; i < select_sql.relations.size(); ++i) {
    const InnerJoinSqlNode &relations = select_sql.relations[i];
    // construct JoinTables
    JoinTables jt;
    // base relation
    jt.push_join_table(table_map[relations.base_relation.first], nullptr);

    const std::vector<pair<string, string>> &join_relations = relations.join_relations;
    for (size_t j = 0; j < join_relations.size(); ++j) {
      FilterStmt *filter_stmt = nullptr;
      RC          rc =
          FilterStmt::create(db, table_map[join_relations[j].first], &table_map, relations.conditions[j], filter_stmt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot construct filter stmt");
        return rc;
      }
      jt.push_join_table(table_map[join_relations[j].first], filter_stmt);
    }
    // push jt to join_tables
    join_tables.emplace_back(std::move(jt));
  }

  // add parent table to binder context, 包含了表的原名和别名的映射
  // 前面先加当前作用域的表，此时再加上父作用域的表，避免重复
  for (auto &parent_table : parent_table_map) {
    binder_context.add_table(parent_table.first, parent_table.second);
  }

  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder               expression_binder(binder_context);
  vector<unique_ptr<Expression>> having_expressions;
  for (auto expression : select_sql.expressions) {
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  vector<unique_ptr<Expression>> group_by_expressions;
  for (auto expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  BaseTable *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db, default_table, &table_map, select_sql.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  OrderByStmt *orderby_stmt = nullptr;
  // For having conditions
  FilterStmt *having_filter_stmt = nullptr;
  if (select_sql.orderbys.size() > 0) {
    vector<unique_ptr<Expression>> expr_for_orderby;
    auto                           collect_aggr_exprs = [&expr_for_orderby](Expression *expr) {
      if (expr->type() == ExprType::AGGREGATION) {
        expr_for_orderby.emplace_back(
            static_cast<AggregateExpr *>(static_cast<AggregateExpr *>(expr)->deep_copy().release()));
      }
    };
    // 用于从 project exprs 中提取所有不在 aggr func expr 中的 field expr
    auto collect_field_exprs = [&expr_for_orderby](Expression *expr) {
      if (expr->type() == ExprType::FIELD) {
        expr_for_orderby.emplace_back(static_cast<FieldExpr *>(static_cast<FieldExpr *>(expr)->deep_copy().release()));
      }
    };
    for (auto &project : group_by_expressions) {
      project->traverse(collect_aggr_exprs);
    }
    for (auto &project : bound_expressions) {
      project->traverse(
          collect_field_exprs, [](const Expression *expr) { return expr->type() != ExprType::AGGREGATION; });
    }

    vector<unique_ptr<OrderBySqlNode>> orderbys_tmp;
    for (auto &node : select_sql.orderbys) {
      RC rc = expression_binder.bind_unbound_field_expression_orderby(node, orderbys_tmp);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind expression failed. rc=%s", strrc(rc));
        return rc;
      }
    }
    rc = OrderByStmt::create(db,
        default_table,
        &table_map,
        // select_sql.orderbys,
        orderbys_tmp,
        orderby_stmt,
        std::move(expr_for_orderby));
    select_sql.orderbys.clear();
    orderbys_tmp.clear();
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct orderby stmt");
      return rc;
    }
  }

  vector<unique_ptr<Expression>> expr_for_having;
  if (select_sql.having_conditions != nullptr) {
    auto collect_aggr_exprs = [&expr_for_having](Expression *expr) {
      if (expr->type() == ExprType::AGGREGATION) {
        expr_for_having.emplace_back(
            static_cast<AggregateExpr *>(static_cast<AggregateExpr *>(expr)->deep_copy().release()));
      }
    };

    rc = expression_binder.bind_expression(select_sql.having_conditions, having_expressions);
    if (rc != RC::SUCCESS) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
    RC rc =
        FilterStmt::create(db, default_table, &table_map, std::move(having_expressions[0].get()), having_filter_stmt);

    for (auto &project : having_expressions) {
      project->traverse(collect_aggr_exprs);
    }

    having_expressions[0].release();
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct having filter stmt");
      return rc;
    }
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->join_tables_.swap(join_tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_  = filter_stmt;
  select_stmt->orderby_stmt_ = orderby_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->having_stmt_ = having_filter_stmt;
  select_stmt->ex_agg_expressions_.swap(expr_for_having);
  
  stmt = select_stmt;
  return RC::SUCCESS;
}
