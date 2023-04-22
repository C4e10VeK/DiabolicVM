#ifndef DVM_TYPES_HPP
#define DVM_TYPES_HPP

#include <iostream>
#include <cstdint>
#include <memory>
#include <variant>

namespace dialang::vm
{
	class BaseObject;

#ifdef __x86_64
	using dvm_float = double;
	using dvm_int = int64_t;
#else
	using dvm_float = float;
	using dvm_int = int32_t;
#endif

	using Object = std::shared_ptr<BaseObject>;
	using ValueVariant = std::variant<dvm_int, dvm_float, std::monostate, std::string, Object>;

	template<typename T, typename ...Args>
	constexpr bool isSameAnyV = (std::is_same_v<T, Args> || ...);

	struct Value
	{
		ValueVariant value_;
		Value() = default;
		Value(std::string value);
		Value(const char *value);
		Value(dvm_int value);
		Value(float value);
		Value(dvm_float value);
		Value(bool value);

		template<typename T>
		inline bool is() const
		{
			if constexpr (isSameAnyV<T, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>)
				return std::holds_alternative<dvm_int>(value_);
			else if constexpr (isSameAnyV<T, float, double>)
				return std::holds_alternative<dvm_float>(value_);
			else
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
			if constexpr (isSameAnyV<T, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>)
				return static_cast<T>(std::get<dvm_int>(value_));
			else if constexpr (isSameAnyV<T, float, double>)
				return static_cast<T>(std::get<dvm_float>(value_));
			else
				return std::get<T>(value_);
		}
		
		inline void print() const
		{
			if (const std::string *val = std::get_if<std::string>(&value_))
			{
				std::cout << *val;
				return;
			}
			if (const dvm_int *val = std::get_if<dvm_int>(&value_))
			{
				std::cout << *val;
				return;
			}
			if (const dvm_float *val = std::get_if<dvm_float>(&value_))
			{
				std::cout << *val;
			}
		}
	};
}

#endif // DVM_TYPES_HPP
