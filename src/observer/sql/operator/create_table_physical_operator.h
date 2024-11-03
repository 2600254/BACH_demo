#pragma once

#include "sql/operator/physical_operator.h"

class Db;
class Trx;
class CreateTableStmt;

/**
 * @brief 物理算子，建表
 * @ingroup PhysicalOperator
 */
class CreateTablePhysicalOperator : public PhysicalOperator
{
public:
  CreateTablePhysicalOperator(Db *db, std::string table_name, std::vector<AttrInfoSqlNode> attr_infos, StorageFormat storage_format = StorageFormat::UNKNOWN_FORMAT)
    : db_(db), table_name_(std::move(table_name)), attr_infos_(std::move(attr_infos)), storage_format_(std::move(storage_format))
  {}

  virtual ~CreateTablePhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::CREATE_TABLE;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;
  StorageFormat storage_format(){
    return storage_format_;
  }
  

private:
  Db *db_ = nullptr;
  std::string table_name_;
  std::vector<AttrInfoSqlNode> attr_infos_;
  StorageFormat storage_format_;
};