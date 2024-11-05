#include "common/type/vector_type.h"
#include "common/value.h"
#include <cmath>

int VectorType::compare(const Value &left, const Value &right) const
{
  if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS) {
    return INT32_MAX;
  }
  Vector left_vector  = left.get_vector();
  Vector right_vector = right.get_vector();
  if (left_vector.dim != right_vector.dim) {
    return INT32_MAX;
  }
  for (int i = 0; i < left_vector.dim; i++) {
    if (left_vector.data[i] < right_vector.data[i]) {
      return -1;
    } else if (left_vector.data[i] > right_vector.data[i]) {
      return 1;
    }
  }
  return 0;
}

RC VectorType::to_string(const Value &val, string &result) const
{
  if (val.attr_type() != AttrType::VECTORS) {
    return RC::UNSUPPORTED;
  }
  Vector vector = val.get_vector();
  result        = "[";
  for (int i = 0; i < vector.dim; i++) {
    result += common::double_to_str(vector.data[i]);
    if (i != vector.dim - 1) {
      result += ",";
    }
  }
  result += "]";
  return RC::SUCCESS;
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const {
  if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS) {
    return RC::UNSUPPORTED;
  }
  Vector left_vector  = left.get_vector();
  Vector right_vector = right.get_vector();
  if (left_vector.dim != right_vector.dim) {
    return RC::UNSUPPORTED;
  }
  Vector result_vector;
  result_vector.dim  = left_vector.dim;
  result_vector.data = new float[left_vector.dim];
  for (int i = 0; i < left_vector.dim; i++) {
    result_vector.data[i] = left_vector.data[i] + right_vector.data[i];
  }
  result.set_vector(result_vector);
  return RC::SUCCESS;
}

RC VectorType::subtract(const Value &left, const Value &right, Value &result) const {
    if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS) {
    return RC::UNSUPPORTED;
  }
  Vector left_vector  = left.get_vector();
  Vector right_vector = right.get_vector();
  if (left_vector.dim != right_vector.dim) {
    return RC::UNSUPPORTED;
  }
  Vector result_vector;
  result_vector.dim  = left_vector.dim;
  result_vector.data = new float[left_vector.dim];
  for (int i = 0; i < left_vector.dim; i++) {
    result_vector.data[i] = left_vector.data[i] - right_vector.data[i];
  }
  result.set_vector(result_vector);
  return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const {
    if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS) {
    return RC::UNSUPPORTED;
  }
  Vector left_vector  = left.get_vector();
  Vector right_vector = right.get_vector();
  if (left_vector.dim != right_vector.dim) {
    return RC::UNSUPPORTED;
  }
  Vector result_vector;
  result_vector.dim  = left_vector.dim;
  result_vector.data = new float[left_vector.dim];
  for (int i = 0; i < left_vector.dim; i++) {
    result_vector.data[i] = left_vector.data[i] * right_vector.data[i];
  }
  result.set_vector(result_vector);
  return RC::SUCCESS;
}

RC VectorType::l2_distance(const Value &left, const Value &right, Value &result) const {
    if(left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS){
        return RC::UNSUPPORTED;
    }
    Vector left_vector = left.get_vector();
    Vector right_vector = right.get_vector();
    if(left_vector.dim != right_vector.dim){
        return RC::UNSUPPORTED;
    }
    float sum = 0;
    for(int i = 0; i < left_vector.dim; i++){
        sum += (left_vector.data[i] - right_vector.data[i]) * (left_vector.data[i] - right_vector.data[i]);
    }
    result.set_float(sqrt(sum));
    return RC::SUCCESS;
}

RC VectorType::cosine_distance(const Value &left, const Value &right, Value &result) const {
    if(left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS){
        return RC::UNSUPPORTED;
    }
    Vector left_vector = left.get_vector();
    Vector right_vector = right.get_vector();
    if(left_vector.dim != right_vector.dim){
        return RC::UNSUPPORTED;
    }
    float sum = 0;
    float left_sum = 0;
    float right_sum = 0;
    for(int i = 0; i < left_vector.dim; i++){
        sum += left_vector.data[i] * right_vector.data[i];
        left_sum += left_vector.data[i] * left_vector.data[i];
        right_sum += right_vector.data[i] * right_vector.data[i];
    }
    result.set_float(fabs(1 - sum / (sqrt(left_sum) * sqrt(right_sum))));
    return RC::SUCCESS;
}

RC VectorType::inner_product(const Value &left, const Value &right, Value &result) const {
    if(left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS){
        return RC::UNSUPPORTED;
    }
    Vector left_vector = left.get_vector();
    Vector right_vector = right.get_vector();
    if(left_vector.dim != right_vector.dim){
        return RC::UNSUPPORTED;
    }
    float sum = 0;
    for(int i = 0; i < left_vector.dim; i++){
        sum += left_vector.data[i] * right_vector.data[i];
    }
    result.set_float(sum);
    return RC::SUCCESS;
}