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
// Created by Wangyunlai on 2022/07/08.
//

#include "sql/operator/vector_index_scan_physical_operator.h"
#include "storage/index/index.h"
#include "storage/trx/trx.h"

VectorIndexScanPhysicalOperator::VectorIndexScanPhysicalOperator(Table *table, Index *index)
    : table_(table), index_(index)
{}

RC VectorIndexScanPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC                rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC VectorIndexScanPhysicalOperator::next()
{
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  return children_[0]->next();
}

RC VectorIndexScanPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple *VectorIndexScanPhysicalOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

RC VectorIndexScanPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC rc = RC::SUCCESS;
  return rc;
}

std::string VectorIndexScanPhysicalOperator::param() const
{
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}
