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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class OrderByStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  class JoinTables
  {
  public:
    JoinTables()  = default;
    ~JoinTables() = default;
    JoinTables(JoinTables &&other)
    {
      join_tables_.swap(other.join_tables_);
      on_conds_.swap(other.on_conds_);
      alias_.swap(other.alias_);
    }
    void push_join_table(BaseTable *table, FilterStmt *fu, const std::string alias = "")
    {
      join_tables_.emplace_back(table);
      on_conds_.emplace_back(fu);
      alias_.emplace_back(alias);
    }
    const std::vector<BaseTable *>  &join_tables() const { return join_tables_; }
    const std::vector<FilterStmt *> &on_conds() const { return on_conds_; }
    const std::vector<std::string>  &alias() const { return alias_; }

  private:
    std::vector<BaseTable *>  join_tables_;
    std::vector<std::string>  alias_;
    std::vector<FilterStmt *> on_conds_;
  };

public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt,
      const std::unordered_map<std::string, BaseTable *> &parent_table_map = {});

public:
  const std::vector<JoinTables> &join_tables() const { return join_tables_; }
  FilterStmt                    *filter_stmt() const { return filter_stmt_; }

  std::vector<std::unique_ptr<Expression>> &query_expressions() { return query_expressions_; }
  std::vector<std::unique_ptr<Expression>> &group_by() { return group_by_; }
  std::vector<std::unique_ptr<Expression>> &ex_agg_expressions() { return ex_agg_expressions_; }
  OrderByStmt                              *orderby_stmt() const { return orderby_stmt_; }
  FilterStmt                               *having_stmt() const { return having_stmt_; }

private:
  std::vector<std::unique_ptr<Expression>> query_expressions_;
  std::vector<JoinTables>                  join_tables_;
  FilterStmt                              *filter_stmt_  = nullptr;
  FilterStmt                              *having_stmt_  = nullptr;
  OrderByStmt                             *orderby_stmt_ = nullptr;
  std::vector<std::unique_ptr<Expression>> group_by_;
  std::vector<std::unique_ptr<Expression>> ex_agg_expressions_;
};
