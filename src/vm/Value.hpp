#ifndef DVM_TYPES_HPP
#define DVM_TYPES_HPP

#include <iostream>
#include <cstdint>
#include <memory>
#include <variant>

namespace dialang::vm
{
	class BaseObject;

	using Object = std::shared_ptr<BaseObject>;
	using ValueVariant = std::variant<uint64_t, int32_t, double, bool, std::monostate, std::string, Object>;

	struct Value
	{
		ValueVariant value_;
		Value() = default;
		Value(std::string value);
		Value(const char *value);
		Value(int32_t value);
		Value(bool value);

		template<typename T>
		inline bool is() const
		{
			return std::holds_alternative<T>(value_);
		}

		template<typename ...Args>
		inline bool isAny() const
		{
			return (is<Args>() || ...);
		}

		template<typename T>
		inline T as() const
		{
			return std::get<T>(value_);
		}
		
		inline void print() const
		{
			if (const std::string *val = std::get_if<std::string>(&value_))
			{
				std::cout << *val;
				return;
			}
			if (const int32_t *val = std::get_if<int32_t>(&value_))
			{
				std::cout << *val;
				return;
			}
			if (const bool *val = std::get_if<bool>(&value_))
			{
				std::cout << std::boolalpha << *val;
				return;
			}
		}
	};
}

#endif // DVM_TYPES_HPP
