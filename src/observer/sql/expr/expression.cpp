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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include <regex>
#include <string>
#include <iomanip>
#include "common/lang/string.h"
#include "sql/expr/arithmetic_operator.hpp"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/stmt/select_stmt.h"
#include "sql/parser/parse_defs.h"

using namespace std;


RC FieldExpr::get_value(const Tuple &tuple, Value &value)
{
  LOG_INFO("%s", tuple.to_string().c_str());
  const char* table_name_str = table_name();
  if(table_name_str == nullptr){
    table_name_str = field_.table_name();
  }
  LOG_INFO("table_name: %s, field_name: %s", table_name_str, field_name());
  if(is_first_){
    bool & is_first_ref = const_cast<bool&>(is_first_);
    is_first_ref = false;
    return tuple.find_cell(TupleCellSpec(table_name_str, field_name()), value, const_cast<int&>(index_));
  }else{
    return tuple.cell_at(index_,value);
  }
}

bool FieldExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::FIELD) {
    return false;
  }
  const auto &other_field_expr = static_cast<const FieldExpr &>(other);
  return table_name() == other_field_expr.table_name() && field_name() == other_field_expr.field_name();
}

// TODO: 在进行表达式计算时，`chunk` 包含了所有列，因此可以通过 `field_id` 获取到对应列。
// 后续可以优化成在 `FieldExpr` 中存储 `chunk` 中某列的位置信息。
RC FieldExpr::get_column(Chunk &chunk, Column &column)
{
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    column.reference(chunk.column(field().meta()->field_id()));
  }
  return RC::SUCCESS;
}


/////////////////////////////////////////////////////////////////////////////////


bool ValueExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::VALUE) {
    return false;
  }
  const auto &other_value_expr = static_cast<const ValueExpr &>(other);
  return value_.compare(other_value_expr.get_value()) == 0;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value)
{
  value = value_;
  return RC::SUCCESS;
}

RC ValueExpr::get_column(Chunk &chunk, Column &column)
{
  column.init(value_);
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }
  rc = Value::cast_to(value, cast_type_, cast_value);
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &result)
{
  Value value;
  if(child_->type() == ExprType::SUBQUERY){
    SubQueryExpr* subquery_expr = static_cast<SubQueryExpr *>(child_.get());
    if(!subquery_expr->has_opened()){
      subquery_expr->open(nullptr);
      subquery_expr->set_opened();
    }
    if(subquery_expr->is_single_value()){
      // 单值子查询，直接获取值,替换原来的子查询表达式
      subquery_expr->get_value(tuple, value);
      subquery_expr->close();
      ValueExpr* value_expr = new ValueExpr(value);
      std::unique_ptr<ValueExpr> value_expr_ptr(value_expr);
      set_child(std::move(value_expr_ptr));
    }else{
      // 多值子查询，获取值后转换为ExprListExpr，替换原来的子查询表达式
      std::vector<Expression*> exprList;
      RC rc = RC::SUCCESS;
      Value subquery_value;
      while (RC::SUCCESS == (rc = subquery_expr->get_value(tuple, subquery_value))) {
        ValueExpr* value_expr = new ValueExpr(subquery_value);
        exprList.push_back(value_expr);
      }
      subquery_expr->close();
      if(subquery_expr->comp() >= EQUAL_TO && subquery_expr->comp() <= GREAT_THAN){
        if(exprList.size() > 1){
          LOG_WARN("subquery return more than one value");
          return RC::INTERNAL;
        }
      }
      if(exprList.size() == 1){
        set_child(std::unique_ptr<Expression>(exprList[0]));
      }else{
        ExprListExpr* expr_list_expr = new ExprListExpr(std::move(exprList));
        std::unique_ptr<ExprListExpr> expr_list_expr_ptr(expr_list_expr);
        set_child(std::move(expr_list_expr_ptr));
      }
    }
  }
  RC rc = child_->get_value(tuple, value);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return cast(value, result);
}

RC CastExpr::try_get_value(Value &result) const
{
  Value value;
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

////////////////////////////////////////////////////////////////////////////////
static void replace_all(std::string &str, const std::string &from, const std::string &to)
{
  if (from.empty()) {
    return;
  }
  size_t pos = 0;
  while (std::string::npos != (pos = str.find(from, pos))) {
    str.replace(pos, from.length(), to);
    pos += to.length();  // in case 'to' contains 'from'
  }
}
static bool str_like(const Value &left, const Value &right)
{
  std::string raw_reg(right.data());
  replace_all(raw_reg, "_", "[^']");
  replace_all(raw_reg, "%", "[^']*");
  std::regex reg(raw_reg.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
  bool res = std::regex_match(left.data(), reg);
  return res;
}

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::ComparisonExpr(CompOp comp, Expression* left, Expression* right)
    : comp_(comp), left_(left), right_(right)
{}

ComparisonExpr::~ComparisonExpr() {}


RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  RC  rc         = RC::SUCCESS;
  // int cmp_result = left.compare(right);
  int cmp_result;
  if(comp_ != LIKE_OP && comp_ != NOT_LIKE_OP)
  {
    cmp_result = left.compare(right);
  }
  result         = false;
  switch (comp_) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    case LIKE_OP :{
      result = str_like(left,right);
    } break;
    case NOT_LIKE_OP:{
      result = !str_like(left,right);
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *  left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr *  right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;
    RC   rc    = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }
  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value)
{
  Value left_value;
  Value right_value;
  
  bool bool_value = false;
  RC rc = RC::SUCCESS;
  if (comp_ == EXISTS_OP || comp_ == NOT_EXISTS_OP) {
    rc = right_->get_value(tuple, right_value);
    value.set_boolean(comp_ == EXISTS_OP ? rc == RC::SUCCESS : rc == RC::RECORD_EOF);
    return RC::RECORD_EOF == rc ? RC::SUCCESS : rc;
  }

  if(comp_ == IN_OP || comp_ == NOT_IN_OP){
    rc = left_->get_value(tuple, left_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
      return rc;
    }
    //右侧如果是一个值list 比如 id in (1,2,3)
    if(right_->type() == ExprType::EXPRLIST){
      static_cast<ExprListExpr*>(right_.get())->reset();
    }

    if(left_->type() == ExprType::CAST){
      CastExpr* cast_expr = static_cast<CastExpr *>(left_.get());
      if(cast_expr->child()->type() == ExprType::EXPRLIST){
        ExprListExpr* eler = static_cast<ExprListExpr *>(cast_expr->child().get());
        eler->reset();
      }
    }
    if(right_->type() == ExprType::CAST){
      CastExpr* cast_expr = static_cast<CastExpr *>(right_.get());
      if(cast_expr->child()->type() == ExprType::EXPRLIST){
        ExprListExpr* eler = static_cast<ExprListExpr *>(cast_expr->child().get());
        eler->reset();
      }
    }
    bool res = false; // 有一样的值
    while (RC::SUCCESS == (rc = right_->get_value(tuple, right_value))) {
      if(left_value.compare(right_value) == 0) {
        res = true;
      }
    }
    if(rc != RC::RECORD_EOF){
      return rc;
    }
    bool_value = comp_ == IN_OP ? res : !res;
    rc = rc == RC::RECORD_EOF ? RC::SUCCESS : rc;
  }else{
    //如果不是in/not in,那么每次比较两侧都仅有一个值
    rc = left_->get_value(tuple, left_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
      return rc;
    }
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
    rc = compare_value(left_value, right_value, bool_value);
  }

  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
  
}

RC ComparisonExpr::eval(Chunk &chunk, std::vector<uint8_t> &select)
{
  RC     rc = RC::SUCCESS;
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  if (left_column.attr_type() != right_column.attr_type()) {
    LOG_WARN("cannot compare columns with different types");
    return RC::INTERNAL;
  }
  if (left_column.attr_type() == AttrType::INTS) {
    rc = compare_column<int>(left_column, right_column, select);
  } else if (left_column.attr_type() == AttrType::FLOATS) {
    rc = compare_column<float>(left_column, right_column, select);
  } else {
    // TODO: support string compare
    LOG_WARN("unsupported data type %d", left_column.attr_type());
    return RC::INTERNAL;
  }
  return rc;
}

template <typename T>
RC ComparisonExpr::compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const
{
  RC rc = RC::SUCCESS;

  bool left_const  = left.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    compare_result<T, true, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else if (left_const && !right_const) {
    compare_result<T, true, false>((T *)left.data(), (T *)right.data(), right.count(), result, comp_);
  } else if (!left_const && right_const) {
    compare_result<T, false, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else {
    compare_result<T, false, false>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  }
  return rc;
}

// void ComparisonExpr::set_left(const std::unique_ptr<Expression> left) {
//   left_ = std::move(left);
// }
// void ComparisonExpr::set_right(const std::unique_ptr<Expression> right) {
//   right_ = std::move(right);
// }

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

bool ArithmeticExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (type() != other.type()) {
    return false;
  }
  auto &other_arith_expr = static_cast<const ArithmeticExpr &>(other);
  return arithmetic_type_ == other_arith_expr.arithmetic_type() && left_->equal(*other_arith_expr.left_) &&
         right_->equal(*other_arith_expr.right_);
}
AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  value.set_type(target_type);

  switch (arithmetic_type_) {
    case Type::ADD: {
      Value::add(left_value, right_value, value);
    } break;

    case Type::SUB: {
      Value::subtract(left_value, right_value, value);
    } break;

    case Type::MUL: {
      Value::multiply(left_value, right_value, value);
    } break;

    case Type::DIV: {
      Value::divide(left_value, right_value, value);
    } break;

    case Type::NEGATIVE: {
      Value::negative(left_value, value);
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
RC ArithmeticExpr::execute_calc(
    const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const
{
  RC rc = RC::SUCCESS;
  switch (type) {
    case Type::ADD: {
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, AddOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, AddOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
    } break;
    case Type::SUB:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, SubtractOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, SubtractOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::MUL:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, MultiplyOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, MultiplyOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::DIV:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, DivideOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, DivideOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::NEGATIVE:
      if (attr_type == AttrType::INTS) {
        unary_operator<LEFT_CONSTANT, int, NegateOperator>((int *)left.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        unary_operator<LEFT_CONSTANT, float, NegateOperator>(
            (float *)left.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    default: rc = RC::UNIMPLEMENTED; break;
  }
  if (rc == RC::SUCCESS) {
    result.set_count(result.capacity());
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
    return rc;
  }
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_column(left_column, right_column, column);
}

RC ArithmeticExpr::calc_column(const Column &left_column, const Column &right_column, Column &column) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  column.init(target_type, left_column.attr_len(), std::max(left_column.count(), right_column.count()));
  bool left_const  = left_column.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right_column.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    column.set_column_type(Column::Type::CONSTANT_COLUMN);
    rc = execute_calc<true, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (left_const && !right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<true, false>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (!left_const && right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, false>(left_column, right_column, column, arithmetic_type_, target_type);
  }
  return rc;
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

////////////////////////////////////////////////////////////////////////////////

UnboundAggregateExpr::UnboundAggregateExpr(const char *aggregate_name, Expression *child)
    : aggregate_name_(aggregate_name), child_(child)
{}

////////////////////////////////////////////////////////////////////////////////
AggregateExpr::AggregateExpr(Type type, Expression *child) : aggregate_type_(type), child_(child) {}

AggregateExpr::AggregateExpr(Type type, unique_ptr<Expression> child) : aggregate_type_(type), child_(std::move(child))
{}

RC AggregateExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    rc = RC::INTERNAL;
  }
  return rc;
}

bool AggregateExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != type()) {
    return false;
  }
  const AggregateExpr &other_aggr_expr = static_cast<const AggregateExpr &>(other);
  return aggregate_type_ == other_aggr_expr.aggregate_type() && child_->equal(*other_aggr_expr.child());
}

unique_ptr<Aggregator> AggregateExpr::create_aggregator() const
{
  unique_ptr<Aggregator> aggregator;
  switch (aggregate_type_) {
    case Type::SUM: {
      aggregator = make_unique<SumAggregator>();
      break;
    }
    case Type::AVG: {
      aggregator = make_unique<AvgAggregator>();
      break;
    }
    case Type::MAX: {
      aggregator = make_unique<MaxAggregator>();
      break;
    }
    case Type::MIN: {
      aggregator = make_unique<MinAggregator>();
      break;
    }
    case Type::COUNT: {
      aggregator = make_unique<CountAggregator>();
      break;
    }
    default: {
      ASSERT(false, "unsupported aggregate type");
      break;
    }
  }
  return aggregator;
}

RC AggregateExpr::get_value(const Tuple &tuple, Value &value)
{
  LOG_INFO("AggregateExpr::get_value is_first_");
  LOG_INFO("AggregateExpr::get_value table_name_:%d",index_);
  TupleCellSpec spec(name());
  //int index = 0;
  // spec.set_agg_type(get_aggr_func_type());
  if(is_first_)
  {
    bool & is_first_ref = const_cast<bool&>(is_first_);
    is_first_ref = false;
    return tuple.find_cell(spec,value,const_cast<int&>(index_));
  }
  else
  {
    return tuple.cell_at(index_,value);
  }
}

RC AggregateExpr::type_from_string(const char *type_str, AggregateExpr::Type &type)
{
  RC rc = RC::SUCCESS;
  if (0 == strcasecmp(type_str, "count")) {
    type = Type::COUNT;
  } else if (0 == strcasecmp(type_str, "sum")) {
    type = Type::SUM;
  } else if (0 == strcasecmp(type_str, "avg")) {
    type = Type::AVG;
  } else if (0 == strcasecmp(type_str, "max")) {
    type = Type::MAX;
  } else if (0 == strcasecmp(type_str, "min")) {
    type = Type::MIN;
  } else {
    rc = RC::INVALID_ARGUMENT;
  }
  return rc;
}

SubQueryExpr::SubQueryExpr(const SelectSqlNode& sql_node) {
  sql_node_ = std::make_unique<SelectSqlNode>(sql_node);
  is_open_ = false;
  is_single_value_ = false;
}

bool SubQueryExpr::has_more_row(const Tuple &tuple) const
{
  return physical_oper_->next() != RC::RECORD_EOF;
}

RC SubQueryExpr::get_value(const Tuple &tuple, Value &value){
  physical_oper_->set_parent_tuple(&tuple);
  // 每次返回一行的第一个 cell
  RC rc = physical_oper_->next();
  if (RC::SUCCESS != rc) {
    return rc;
  }
  return physical_oper_->current_tuple()->cell_at(0, value);
}

RC SubQueryExpr::open(Trx* trx) {return physical_oper_->open(trx);}

RC SubQueryExpr::close() {
  is_open_ = false;
  return physical_oper_->close();
}

RC SubQueryExpr::generate_select_stmt(Db* db, const std::unordered_map<std::string, Table *> &tables){
  Stmt * select_stmt = nullptr;
  RC rc = SelectStmt::create(db, *sql_node_.get(), select_stmt); 
  if (OB_FAIL(rc)) {
    return rc;
  }
  if (select_stmt->type() != StmtType::SELECT) {
    return RC::INVALID_ARGUMENT;
  }
  SelectStmt* ss = static_cast<SelectStmt*>(select_stmt);
  if (ss->query_expressions().size() > 1) {
    return RC::INVALID_ARGUMENT;
  }
  //判断subquery中是否是聚合函数，如果是聚合函数那么subquery返回的结果是单值
  if(ss->query_expressions()[0]->type() == ExprType::UNBOUND_AGGREGATION 
    || ss->query_expressions()[0]->type() == ExprType::AGGREGATION){
      is_single_value_ = true;
  }
  stmt_ = std::unique_ptr<SelectStmt>(ss);
  return RC::SUCCESS;
}
RC SubQueryExpr::generate_logical_oper(){
  LogicalPlanGenerator lpg;
  if (RC rc = lpg.create(stmt_.get(), logical_oper_); OB_FAIL(rc)) {
    LOG_WARN("subquery logical oper generate failed. return %s", strrc(rc));
    return rc;
  }
  return RC::SUCCESS;
}
RC SubQueryExpr::generate_physical_oper(){
  PhysicalPlanGenerator ppg;
  if (RC rc = ppg.create(*logical_oper_, physical_oper_); OB_FAIL(rc)) {
    LOG_WARN("subquery physical oper generate failed. return %s", strrc(rc));
    return rc;
  }
  return RC::SUCCESS;
}