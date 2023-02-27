#ifndef DVM_OBJECT_HPP
#define DVM_OBJECT_HPP

#include <string>
#include "../utils.hpp"
#include "../OpCodes.hpp"

namespace dialang::vm
{

	struct BaseObject
	{
		DiaBcTypes type_;
		bool isSigned_ = false;

		virtual ~BaseObject() = default;

		virtual std::string toString() = 0;
	};

	template<typename T, DiaBcTypes>
	struct BaseObjectGen : public BaseObject
	{
		T value_;

		std::string toString() override
		{
			return utils::toString(value_);
		}
	};

	using StringObject = BaseObjectGen<std::string, TYPE_STRING>;
	using I32Object = BaseObjectGen<int32_t, TYPE_DWORD>;
	using I64Object = BaseObjectGen<int64_t, TYPE_QWORD>;

}

#endif // DVM_OBJECT_HPP
