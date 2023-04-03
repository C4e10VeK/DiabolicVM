#ifndef DVM_OBJECT_HPP
#define DVM_OBJECT_HPP

#include "Value.hpp"
#include <stdint.h>
#include <vcruntime.h>

namespace dialang::vm
{

	enum class ObjectType
	{
		Single,
		Array
	};

	class BaseObject
	{
	public:
		virtual ~BaseObject() = default;
		virtual std::string getObjectName() const;

		template<class T>
		inline bool is()
		{
			return dynamic_cast<T *>(this);
		}

		template<class T>
		inline T &as()
		{
			return reinterpret_cast<T &>(this);
		}
	};

	template<class T>
	class BaseObjectGen : public BaseObject
	{
	private:
		T m_value;
	public:

		inline std::string getObjectName() const override
		{
			return typeid(T).name();
		}

		inline const T &get() const
		{
			return m_value;
		}

		inline T &get()
		{
			return m_value;
		}
	};

	class ObjectArray : public BaseObject
	{
	private:
		Value *m_array;
		size_t m_size;
		const ObjectType m_type = ObjectType::Array;
	public:
		ObjectArray() = default;
		ObjectArray(size_t size)
			: m_array(new Value[size]),
			  m_size(size) 
		{ }

		~ObjectArray()
		{
			delete[] m_array;
		}

		inline ObjectType getType() const
		{
			return m_type;
		}

		inline std::string getObjectName() const override
		{
			return "";
		}

		inline size_t getSize() const
		{
			return m_size;
		}

		inline const Value &operator[](size_t n) const
		{
			return m_array[n];
		}

		inline Value &operator[](size_t n)
		{
			return m_array[n];
		}
	};
}

#endif // DVM_OBJECT_HPP
