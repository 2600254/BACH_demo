#include "sql/operator/update_logical_operator.h"
UpdateLogicalOperator::UpdateLogicalOperator(BaseTable *table, std::vector<Expression *> expressions, std::vector<FieldMeta> fields)
    : table_(table), expressions_(std::move(expressions)), fields_(fields)
{
}