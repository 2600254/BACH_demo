#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, Value *value, FieldMeta *field)
:table_(table), value_(value), field_(field){}
