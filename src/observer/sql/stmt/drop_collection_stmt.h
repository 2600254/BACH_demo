#pragma once

#include <string>

#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示删除表的语句
 * @ingroup Statement
 */
class DropCollectionStmt : public Stmt
{
public:
DropCollectionStmt(const std::string &collection_name) : collection_name_(collection_name){}
  virtual ~DropCollectionStmt() = default;

  StmtType type() const override { return StmtType::DROP_TABLE; }

  const std::string                  &collection_name() const { return collection_name_; }

  static RC            create(Db *db, const DropCollectionNode &drop_collection, Stmt *&stmt);

private:
  std::string                  collection_name_;
};