#ifndef DVM_TYPES_HPP
#define DVM_TYPES_HPP

#include <cstdint>
#include <variant>
#include "Object.hpp"

namespace dialang::vm
{
	using String = std::shared_ptr<StringObject>;
	using ValueType = std::variant<int32_t, bool, std::monostate, String>;

	struct Value
	{
		ValueType value_;
		Value(int32_t value) : value_(value) { }
		Value(bool value) : value_(value) { }
		Value(std::string value) : value_(std::make_shared<StringObject>(std::move(value))) { }
		Value(const char *value) : value_(std::make_shared<StringObject>(value)) { }

		template<typename T>
		inline bool is() const
		{
			return std::holds_alternative<T>(value_);
		}

		template<typename T>
		inline T as() const
		{
			return std::get<T>(value_);
		}
		
	};

	inline bool operator==(const Value &lhs, const Value &rhs)
	{
		if (lhs.is<int32_t>() && rhs.is<int32_t>())
			return true;

		if (lhs.is<bool>() && rhs.is<bool>())
			return true;

		return false;
	}

	inline Value operator+(const Value &lhs, const Value &rhs)
	{
		if (lhs.is<int32_t>() && rhs.is<int32_t>())
			return Value(lhs.as<int32_t>() + rhs.as<int32_t>());
		
		return lhs;
	}

	inline Value operator+=(const Value &lhs, const Value &rhs)
	{
		if (lhs.is<int32_t>() && rhs.is<int32_t>())
			return Value(lhs.as<int32_t>() + rhs.as<int32_t>());
		
		return lhs;
	}
}

#endif // DVM_TYPES_HPP
