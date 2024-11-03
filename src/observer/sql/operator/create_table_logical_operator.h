#include "sql/operator/logical_operator.h"

class Db;

class CreateTableLogicalOperator : public LogicalOperator 
{
public:
  CreateTableLogicalOperator(Db *db, const std::string &table_name, const std::vector<AttrInfoSqlNode> &attr_infos, StorageFormat storage_format = StorageFormat::UNKNOWN_FORMAT)
    : db_(db),table_name_(table_name), attr_infos_(attr_infos), storage_format_(storage_format)
  {}
  virtual ~CreateTableLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::CREATE_TABLE;
  }

  std::string &table_name() 
  { 
    return table_name_; 
  }
  std::vector<AttrInfoSqlNode> &attr_infos()
  {
    return attr_infos_;
  }
  Db *get_db()
  {
    return db_;
  }

  StorageFormat storage_format(){
    return storage_format_;
  }
private:
  Db *db_ = nullptr;
  std::string table_name_;
  std::vector<AttrInfoSqlNode> attr_infos_;
  StorageFormat storage_format_;
};