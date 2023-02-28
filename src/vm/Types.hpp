#ifndef DVM_TYPES_HPP
#define DVM_TYPES_HPP

#include <cstdint>

namespace dialang::vm
{
	enum class ValueType
	{
		Boolean,
		Nil,
		Number
	};

	struct Value
	{
		ValueType type;
		union
		{
			bool boolean;
			int32_t int32;
		} as;

		Value(int32_t val) : type(ValueType::Number)
		{
			as.int32 = val;
		}
	};
}

#endif // DVM_TYPES_HPP
