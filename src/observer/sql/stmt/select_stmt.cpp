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
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;

  // collect tables in `from` statement
  vector<Table *>                tables;
  unordered_map<string, Table *> table_map;
  unordered_map<string, Table *> local_table_map;
  vector<JoinTables> join_tables;

  
  // collect tables in `from` statement
  auto check_and_collect_tables = [&](const char* table_name) {
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null.");
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    LOG_INFO("get here: such table. db=%s, table_name=%s", db->name(), table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
    local_table_map.insert({table_name, table});
    return RC::SUCCESS;
  };
  
  // 先收集所有的 condition
  std::vector<ConditionSqlNode>& all_conditions = const_cast<std::vector<ConditionSqlNode>&>(select_sql.conditions);
  for (size_t i = 0; i < select_sql.relations.size(); ++i) {
    const InnerJoinSqlNode& relations = select_sql.relations[i];
    std::vector<std::vector<ConditionSqlNode>>& conditions = const_cast<decltype(relations.conditions)&>(relations.conditions);
    for (auto& on_conds : conditions) {
      all_conditions.insert(all_conditions.end(), on_conds.begin(), on_conds.end());
      on_conds.clear();
    }
    conditions.clear();
  }

  auto cond_is_ok = [&local_table_map](const ConditionSqlNode& node) {
    if (node.left_is_attr && local_table_map.count(node.left_attr.relation_name) == 0)  {
      return false;
    }
    if (node.right_is_attr && local_table_map.count(node.right_attr.relation_name) == 0)  {
      return false;
    }
    return true;
  };

  auto pick_conditions = [&cond_is_ok, &all_conditions]() {
    std::vector<ConditionSqlNode> res;
    for (auto iter = all_conditions.begin(); iter != all_conditions.end(); ) {
      if (cond_is_ok(*iter)) {
        res.emplace_back(*iter);
        iter = all_conditions.erase(iter);
      } else {
        iter++;
      }
    }
    return res;
  };

  auto process_one_relation = [&](const std::string& relation, JoinTables& jt) {
    RC rc = RC::SUCCESS;
    if (rc = check_and_collect_tables(relation.c_str()); rc != RC::SUCCESS) {
      return rc;
    }
    auto ok_conds = pick_conditions();
    // create FilterStmt
    FilterStmt* filter_stmt = nullptr;
    if (!ok_conds.empty()) {
      if (rc = FilterStmt::create(db, table_map[relation], &table_map, ok_conds.data(), ok_conds.size(), filter_stmt);
              rc != RC::SUCCESS) {
        return rc;
      }
      ASSERT(nullptr != filter_stmt, "FilterStmt is null!");
    }
    // fill JoinTables
    jt.push_join_table(table_map[relation], filter_stmt);
    return rc;
  };

  for (size_t i = 0; i < select_sql.relations.size(); ++i) {
    const InnerJoinSqlNode& relations = select_sql.relations[i];
    local_table_map.clear();

    // construct JoinTables
    JoinTables jt;

    // base relation
    RC rc = process_one_relation(relations.base_relation, jt);
    if (RC::SUCCESS != rc) {
      return rc;
    }

    const std::vector<std::string>& join_relations = relations.join_relations;
    for (size_t j = 0; j < join_relations.size(); ++j) {
      if (RC::SUCCESS != (rc = process_one_relation(join_relations[j], jt))) {
        return rc;
      }
    }

    // push jt to join_tables
    join_tables.emplace_back(std::move(jt));
  }

  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context);
  
  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      all_conditions.data(),
      static_cast<int>(all_conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  OrderByStmt *orderby_stmt = nullptr;
  if(select_sql.orderbys.size() > 0) {
    vector<unique_ptr<Expression>> expr_for_orderby;
    auto collect_aggr_exprs = [&expr_for_orderby](Expression * expr) {
      if (expr->type() == ExprType::AGGREGATION) {
        expr_for_orderby.emplace_back(static_cast<AggregateExpr*>(static_cast<AggregateExpr*>(expr)->deep_copy().release()));
      }
    };
    // 用于从 project exprs 中提取所有不在 aggr func expr 中的 field expr
    auto collect_field_exprs = [&expr_for_orderby](Expression * expr) {
      if (expr->type() == ExprType::FIELD) {
        expr_for_orderby.emplace_back(static_cast<FieldExpr*>(static_cast<FieldExpr*>(expr)->deep_copy().release()));
      }
    };
    for (auto& project : group_by_expressions) {
      project->traverse(collect_aggr_exprs);
    }
    for (auto& project : bound_expressions) {
      project->traverse(collect_field_exprs, [](const Expression* expr) { return expr->type() != ExprType::AGGREGATION; });
    }
    
    vector<unique_ptr<OrderBySqlNode>>     orderbys_tmp;
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

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->join_tables_.swap(join_tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->orderby_stmt_ = orderby_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  stmt                      = select_stmt;
  return RC::SUCCESS;
}
