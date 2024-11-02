#include "sql/stmt/create_view_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "event/sql_debug.h"
#include "sql/expr/expression.h"
#include "common/types.h"
#include "common/value.h"

static int ATTR_TYPE_LENGTH[] = { -1, 4, 4, 4, 4, 4, 8, 65535, 4, -1 };

CreateViewStmt::CreateViewStmt(bool allow_write, 
                              const std::string view_name,  
                              const std::vector<AttrInfoSqlNode> attr_infos, 
                              std::vector<Field> map_fields, StorageFormat storage_format, 
                              SelectSqlNode *select_sql)
  : allow_write_(allow_write), view_name_(std::move(view_name)), 
    attr_infos_(std::move(attr_infos)), map_fields_(std::move(map_fields)), storage_format_(storage_format)
{
  select_sql_.deep_copy(*select_sql);
}

RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt, SelectSqlNode &select_sql)
{
  StorageFormat storage_format = StorageFormat::UNKNOWN_FORMAT;
  
  bool allow_write = true;
  if (create_view.storage_format.length() == 0) {
    storage_format = StorageFormat::ROW_FORMAT;
  } else {
    storage_format = get_storage_format(create_view.storage_format.c_str());
  }
  if (storage_format == StorageFormat::UNKNOWN_FORMAT) {
    return RC::INVALID_ARGUMENT;
  }
  
  Stmt *sub_stmt = nullptr;
  SelectSqlNode sql_back;
  sql_back.deep_copy(select_sql);
  RC rc = SelectStmt::create(db, select_sql, sub_stmt);
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to create select_stmt when create_view_select, rc=%s", strrc(rc));
    return rc;
  }

  std::vector<Field> map_fields;
  std::vector<AttrInfoSqlNode> attr_infos;
  SelectStmt *select_stmt = static_cast<SelectStmt*>(sub_stmt);
  for (std::unique_ptr<Expression> &attr_expr : select_stmt->query_expressions()) {
    Field map_field;
    AttrInfoSqlNode attr_info;
    if (0 != attr_expr->alias().length()) {
      size_t pos = attr_expr->alias().find('.');
      if (std::string::npos == pos) {
        attr_info.name = attr_expr->alias();
      } else {
        attr_info.name = attr_expr->alias().substr(pos + 1);
      }
    } else {
      attr_info.name = attr_expr->name();
    }
    attr_info.type = attr_expr->value_type();

    if (ExprType::FIELD == attr_expr->type()) {
      FieldExpr *field_expr = dynamic_cast<FieldExpr*>(attr_expr.get());
      map_field = field_expr->field();
      attr_info.length = field_expr->get_field_meta().len();
      attr_info.nullable = field_expr->get_field_meta().nullable();
    } else {
      allow_write = false;
      if (ExprType::VALUE == attr_expr->type()) {
        ValueExpr *value_expr = dynamic_cast<ValueExpr*>(attr_expr.get());
        attr_info.length = value_expr->get_value().length();
      } else {
        attr_info.length = ATTR_TYPE_LENGTH[(int)attr_expr->value_type()];
      }
      // 遍历子表达式，有nullable的FieldExpr时，才允许为NULL
      bool nullable = false;
      auto check_expr_nullable = [&nullable](Expression *expr) {
        if (ExprType::FIELD == expr->type()) {
          FieldMeta field = static_cast<FieldExpr*>(expr)->get_field_meta();
          if (field.nullable()) {
            nullable = true;
          } 
        }
      };
      attr_expr->traverse(check_expr_nullable);
      attr_info.nullable = nullable;
    }
    map_fields.emplace_back(map_field);
    attr_infos.emplace_back(attr_info);
  }

  stmt = new CreateViewStmt(allow_write, std::move(create_view.view_name), 
                            std::move(attr_infos), std::move(map_fields), storage_format, &sql_back);
  sql_debug("create table statement: table name %s", create_view.view_name.c_str());
  return RC::SUCCESS;
}

StorageFormat CreateViewStmt::get_storage_format(const char *format_str) {
  StorageFormat format = StorageFormat::UNKNOWN_FORMAT;
  if (0 == strcasecmp(format_str, "ROW")) {
    format = StorageFormat::ROW_FORMAT;
  } else if (0 == strcasecmp(format_str, "PAX")) {
    format = StorageFormat::PAX_FORMAT;
  } else {
    format = StorageFormat::UNKNOWN_FORMAT;
  }
  return format;
}
