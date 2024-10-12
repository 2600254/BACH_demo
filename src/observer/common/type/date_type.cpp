#include "common/type/date_type.h"
#include "common/lang/comparator.h"
#include <sstream>
#include "common/value.h" 
#include "common/log/log.h"
#include <iomanip>

  
int DateType::compare(const Value &left, const Value &right) const {
    return common::compare_int((void *)&left.value_.int_value_, (void *)&right.value_.int_value_);
}

RC DateType::to_string(const Value &val, string &result) const {
    //yyyy-mm-dd
    stringstream ss;
    int year = val.value_.int_value_ / 10000;
    int month = (val.value_.int_value_ % 10000) / 100;
    int day = val.value_.int_value_ % 100;
    ss << std::setw(4) << std::setfill('0') << year 
    << "-" << std::setw(2) << std::setfill('0') << month 
    << "-" << std::setw(2) << std::setfill('0') << day;
    result = ss.str();
    return RC::SUCCESS;
}