#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"
#include "common/types.h"

class Db;
class Field;

/**
 * @brief 表示创建试图的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateViewStmt : public Stmt
{
public:
  CreateViewStmt(bool allow_write, const std::string view_name,  
                const std::vector<AttrInfoSqlNode> attr_infos, std::vector<Field> map_fields,
                StorageFormat storage_format, SelectSqlNode *select_sql);

  virtual ~CreateViewStmt() = default;

  static RC create(Db *db, const CreateViewSqlNode &create_table, Stmt *&stmt, SelectSqlNode &select_sql);

public:
  bool allow_write() const { return allow_write_; }
  std::string view_name() const { return view_name_; }
  const std::vector<AttrInfoSqlNode> &attr_infos() const { return attr_infos_; }
  const StorageFormat                 storage_format() const { return storage_format_; }
  const std::vector<Field> &map_fields() const { return map_fields_; }
  SelectSqlNode *get_select_sql_node() { return &select_sql_; }
  static StorageFormat get_storage_format(const char *format_str);
  
  StmtType type() const override { return StmtType::CREATE_VIEW; }

private:
  bool allow_write_ = false;                // 是否允许对视图进行写操作
  std::string view_name_;
  std::vector<AttrInfoSqlNode> attr_infos_; // 视图列信息
  std::vector<Field> map_fields_;           // col映射到的原始列，里面有table、fieldMeta
  StorageFormat                storage_format_;
  SelectSqlNode select_sql_;     // SelectStmt里存的是指针，不便于落盘管理
};