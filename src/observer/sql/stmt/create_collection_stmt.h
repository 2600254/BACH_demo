#pragma once

#include <string>

#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示创建集合的语句
 * @ingroup Statement
 */
class CreateCollectionStmt : public Stmt
{
public:
    CreateCollectionStmt(Db *db, const std::string &collection_name)
      : db_(db),
        collection_name_(collection_name){}

  virtual ~CreateCollectionStmt() = default;

  StmtType type() const override { return StmtType::CREATE_COLLECTION; }

  const std::string                  &collection_name() const { return collection_name_; }

  static RC            create(Db *db, const CreateCollectionNode &create_collection, Stmt *&stmt);
  Db                  *get_db() const { return db_; }

private:
  Db                          *db_ = nullptr;
  std::string                  collection_name_;
};