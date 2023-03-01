#ifndef DVM_OBJECT_HPP
#define DVM_OBJECT_HPP

#include <functional>
#include <string>
#include <type_traits>
#include "../utils.hpp"

namespace dialang::vm
{

	struct BaseObject
	{
		enum class Type
		{
			TYPE_STRING,
			TYPE_FUNCTION
		};

		Type type_;

		BaseObject() = default;

		BaseObject(Type type) : type_(type) { }

		virtual ~BaseObject() = default;

		virtual std::string toString() = 0;
	};	

	template<typename T, BaseObject::Type ObjType>
	struct BaseObjectGen : public BaseObject
	{
		T value_;

		BaseObjectGen() : BaseObject(ObjType) { }
		BaseObjectGen(T value) : BaseObject(ObjType), value_(value) { }

		std::string toString() override
		{
			return utils::toString(value_);
		}
	};

	using StringObject = BaseObjectGen<std::string, BaseObject::Type::TYPE_STRING>;

	inline StringObject operator+(const StringObject &lhs, const StringObject &rhs)
	{
		return StringObject(lhs.value_ + rhs.value_);
	}
}

#endif // DVM_OBJECT_HPP
