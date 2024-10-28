/* Copyright (c) OceanBase and/or its affiliates. All rights reserved.
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
#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"
#include "common/types.h"

class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, std::vector<Expression *> expressions, std::vector<FieldMeta> fields);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table                     *table() const { return table_; }
  std::vector<Expression *> &expressions() { return expressions_; }
  std::vector<FieldMeta>    &fields() { return fields_; }

private:
  Table                    *table_ = nullptr;
  std::vector<Expression *> expressions_;
  std::vector<FieldMeta>    fields_;
};