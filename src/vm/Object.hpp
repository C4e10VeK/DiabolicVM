#ifndef DVM_OBJECT_HPP
#define DVM_OBJECT_HPP

#include <functional>
#include <string>
#include "../utils.hpp"

namespace dialang::vm
{

	struct BaseObject
	{
		enum class Type
		{
			TYPE_CHAR,
			TYPE_I32,
			TYPE_I64,
			TYPE_STRING,
			TYPE_FUNCTION
		};

		Type type_;

		BaseObject() = default;

		BaseObject(Type type) : type_(type) { }

		virtual ~BaseObject() = default;

		virtual std::string toString() = 0;

		template<Type t>
		bool is()
		{
			return type_ == t;
		}

		template<typename T>
		T *as()
		{
			return reinterpret_cast<T *>(this);
		}
	};	

	template<typename T, BaseObject::Type ObjType>
	struct BaseObjectGen : public BaseObject
	{
		T value_;

		BaseObjectGen() : BaseObject(ObjType) { }

		std::string toString() override
		{
			return utils::toString(value_);
		}
	};

	using StringObject = BaseObjectGen<std::string, BaseObject::Type::TYPE_STRING>;
	using I32Object = BaseObjectGen<int32_t, BaseObject::Type::TYPE_I32>;
	using I64Object = BaseObjectGen<int64_t, BaseObject::Type::TYPE_I64>;

	using FnNativeType = std::function<bool(void)>;

	template<>
	struct BaseObjectGen<FnNativeType, BaseObject::Type::TYPE_FUNCTION> : public BaseObject
	{
		FnNativeType native_;

		std::string name_;

		BaseObjectGen() : BaseObject(BaseObject::Type::TYPE_FUNCTION) { }

		std::string toString() override
		{
			return name_ + ": fn(...)";
		}
	};

	using NativeFnObject = BaseObjectGen<FnNativeType, BaseObject::Type::TYPE_FUNCTION>;

}

#endif // DVM_OBJECT_HPP
