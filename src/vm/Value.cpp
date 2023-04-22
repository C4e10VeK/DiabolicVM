#include "Value.hpp"

namespace dialang::vm
{
	Value::Value(std::string value) : value_(std::move(value)) { }
	Value::Value(const char *value) : value_(value) { }
	Value::Value(dvm_int value) : value_(value) { }
	Value::Value(float value) : value_(static_cast<dvm_float>(value)) { }
	Value::Value(dvm_float value) : value_(value) { }
	Value::Value(bool value) : value_(value) { }
}