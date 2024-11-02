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
// Created by WangYunlai on 2022/6/7.
//

#pragma once

#include "storage/field/field_meta.h"
#include <iostream>

class TupleCellSpec final
{
public:
  TupleCellSpec() = default;
  TupleCellSpec(const char *table_name, const char *field_name, const char *alias = nullptr);
  explicit TupleCellSpec(const char *alias);
  explicit TupleCellSpec(const std::string &alias);

  const char *table_name() const { return table_name_.c_str(); }
  const char *field_name() const { return field_name_.c_str(); }
  const char *alias() const { return alias_.c_str(); }

  bool equals(const TupleCellSpec &other) const
  {
    std::string this_table_name  = std::string(table_name());
    std::string other_table_name = std::string(other.table_name());
    std::string this_field_name  = std::string(field_name());
    std::string other_field_name = std::string(other.field_name());
    std::string this_alias_name = std::string(alias());
    std::string other_alias_name = std::string(other.alias());

    if (other_alias_name.find('.') == std::string::npos && this_alias_name.find('.') != std::string::npos){
      other_alias_name = other_table_name + "." + other_alias_name;
    }

    return this_table_name == other_table_name && this_field_name == other_field_name && this_alias_name == other_alias_name;
    // return this_table_name == other_table_name && this_field_name == other_field_name;
  }

private:
  std::string table_name_;
  std::string field_name_;
  std::string alias_;
};
