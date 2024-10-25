/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/log/log.h"
#include "common/type/char_type.h"
#include "common/value.h"
#include "common/time/datetime.h"

int CharType::compare(const Value &left, const Value &right) const
{
  if (left.is_null() || right.is_null()) {
    return common::compare_null(left.is_null(), right.is_null());
  }
  
  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

RC CharType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::DATES:{
      result.set_type(AttrType::DATES);
      int year = 0, month = 0, day = 0;
      if(sscanf(val.value_.pointer_value_, "%d-%d-%d", &year, &month, &day) != 3){
        LOG_WARN("invalid date format: %s", val.value_.pointer_value_);
        return RC::INVALID_ARGUMENT;
      }
      bool is_valid = common::check_date(year, month, day);
      if(!is_valid){
        LOG_WARN("invalid date: %d-%d-%d", year, month, day);
        return RC::INVALID_ARGUMENT;
      }
      result.set_date(year, month, day);
    }break;
    case AttrType::INTS:{
      result.set_int(atoi(val.value_.pointer_value_));
    }break;
    case AttrType::FLOATS:{
      result.set_float(atof(val.value_.pointer_value_));
    }break;
    case AttrType::NULLS:{
      return RC::SUCCESS;
    }break;
    default: return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}

int CharType::cast_cost(AttrType type) const
{
  if (type == AttrType::CHARS) {
    return 0;
  }
  if (type == AttrType::DATES){
    return 1;
  }
  if (type == AttrType::INTS){
    return 2;
  }
  if (type == AttrType::FLOATS){
    return 3;
  }
  
  return INT32_MAX;
}

RC CharType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}