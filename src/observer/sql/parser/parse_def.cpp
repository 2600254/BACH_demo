#include "sql/parser/parse_defs.h"
#include "sql/expr/expression.h"

void OrderBySqlNode::deep_copy(const OrderBySqlNode &src)
{
  if (nullptr != src.expr) {
    expr = src.expr->deep_copy().release();
  }
  is_asc = src.is_asc;
}

void InnerJoinSqlNode::deep_copy(const InnerJoinSqlNode &src)
{
  base_relation = src.base_relation;
  join_relations.clear();
  join_relations = src.join_relations;
  conditions.clear();
  for (size_t i = 0; i < src.conditions.size(); i++) {
    conditions.emplace_back(src.conditions[i]->deep_copy().release());
  }
}

void SelectSqlNode::deep_copy(const SelectSqlNode &src)
{
  expressions.clear();
  for (size_t i = 0; i < src.expressions.size(); i++) {
    expressions.emplace_back(src.expressions[i]->deep_copy().release());
  }
  relations.clear();
  for (size_t i =0; i < src.relations.size(); i++) {
    InnerJoinSqlNode dst;
    dst.deep_copy(src.relations[i]);
    relations.emplace_back(std::move(dst));
  }
  if (nullptr != src.conditions) {
    conditions = src.conditions->deep_copy().release();
  }
  orderbys.clear();
  for (size_t i = 0; i < src.orderbys.size(); i++) {
    OrderBySqlNode dst;
    dst.deep_copy(src.orderbys[i]);
    orderbys.emplace_back(std::move(dst));
  }
  group_by.clear();
  for (size_t i = 0; i < src.group_by.size(); i++) {
    group_by.emplace_back(src.group_by[i]->deep_copy().release());
  }
}
