#include "Value.hpp"

namespace dialang::vm
{
	Value::Value(std::string value) : value_(std::move(value)) { }
	Value::Value(const char *value) : value_(value) { }
	Value::Value(int32_t value) : value_(value) { }
	Value::Value(bool value) : value_(value) { }
}