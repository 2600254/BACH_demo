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

UpdateStmt::UpdateStmt(Table *table, Value *value, FieldMeta *field, FilterStmt *filter_stmt)
    : table_(table), value_(value), field_(field), filter_stmt_(filter_stmt)
{}


UpdateStmt::~UpdateStmt(){
  if (filter_stmt_ != nullptr) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}


RC UpdateStmt::create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt) {
  const char *table_name = update_sql.relation_name.c_str();
  if ( db == nullptr || table_name == nullptr) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (table == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  Value *value = const_cast<Value*>(&update_sql.value);
  const TableMeta &table_meta = table->table_meta();
  FieldMeta *field = const_cast<FieldMeta*>(table_meta.field(update_sql.attribute_name.c_str()));
  if (field == nullptr) {
    LOG_WARN("no such field. table_name=%s, field_name=%s", table_name, update_sql.attribute_name.c_str());
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }
  
  bool valid = false;
  if (nullptr != field) {
    if (AttrType::TEXTS == field->type() && AttrType::CHARS == value->attr_type()) {
      if (MAX_TEXT_LENGTH < value->length()) {
        LOG_WARN("Text length:%d, over max_length 65535", value->length());
        return RC::INVALID_ARGUMENT;
      }
      valid = true;
    }
  }
  if (!valid) {
    LOG_WARN("update field type mismatch. table=%s", table_name);
    return RC::INVALID_ARGUMENT;
  }

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, update_sql.conditions.data(), static_cast<int>(update_sql.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  stmt = new UpdateStmt(table, value, field, filter_stmt);
  return RC::SUCCESS;
}
