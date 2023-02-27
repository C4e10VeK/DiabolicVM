#ifndef DVM_VIRTUALMACHINE_HPP
#define DVM_VIRTUALMACHINE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include "../utils.hpp"

namespace dialang::vm
{
	struct BaseObject
	{
		enum Type
		{
			TYPE_CHAR,
			TYPE_I32,
			TYPE_I64,
			TYPE_STRING,
			TYPE_FUNCTION
		};

		Type type_;

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

	template<typename T>
	struct BaseObjectGen : public BaseObject
	{
		T value_;

		std::string toString() override
		{
			return utils::toString(value_);
		}
	};

	using StringObject = BaseObjectGen<std::string>;
	using I32Object = BaseObjectGen<int32_t>;
	using I64Object = BaseObjectGen<int64_t>;

	class Chunk
	{
	private:
		std::vector<BaseObject *> m_constants;
		std::vector<uint8_t> m_code;
	public:

		~Chunk()
		{
			for (const auto &constant : m_constants)
				delete constant;
		}

		void write(uint8_t code)
		{
			m_code.emplace_back(code);
		}

		int32_t addConstant(BaseObject *object)
		{
			m_constants.emplace_back(object);
			return m_constants.size() - 1;
		}
	};
}

#endif // DVM_VIRTUALMACHINE_HPP
