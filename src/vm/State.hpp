#ifndef DVM_STATE_HPP
#define DVM_STATE_HPP

#include <vector>
#include <cassert>
#include "Object.hpp"
#include "../OpCodes.hpp"

#define assert_message(pred, text) assert(pred && text)

namespace dialang::vm
{

	struct Stack
	{
		int32_t top;
		std::vector<BaseObject *> objects_;

		void free()
		{
			for (const auto &obj : objects_)
				delete obj;
		}

		BaseObject *&operator[](size_t index)
		{
			if (index >= objects_.size())
				objects_.resize(index + 1);

			return objects_[index];
		}
	};

	class State
	{
	private:
		std::vector<uint8_t> m_code;
		uint32_t m_ip;
	public:
		State()
		{
			m_ip = 0;
		}


	};
}

#endif // DVM_STATE_HPP
