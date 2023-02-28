#ifndef DVM_VIRTUALMACHINE_HPP
#define DVM_VIRTUALMACHINE_HPP

#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>
#include "OpCodes.hpp"
#include "Object.hpp"

namespace dialang::vm
{

	class Chunk
	{
	private:
		std::vector<BaseObject *> m_constants;
		std::vector<uint8_t> m_code;
	public:

		~Chunk()
		{
			for (auto &constant : m_constants)
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

		int32_t addConstant(I32Object &object)
		{
			m_constants.emplace_back(new I32Object(object));
			return m_constants.size() - 1;
		}

		int32_t addConstant(I64Object &object)
		{
			m_constants.emplace_back(new I64Object(object));
			return m_constants.size() - 1;
		}

		int32_t addConstant(StringObject &object)
		{
			m_constants.emplace_back(new StringObject(object));
			return m_constants.size() - 1;
		}

		uint8_t *getFirstOp()
		{
			return &m_code[0];
		}

		BaseObject *getConstant(int32_t index)
		{
			return m_constants[index];
		}
	};

	class VM
	{
	private:
		Chunk *m_chunk;
		uint8_t *m_ip;
	public:
		enum class InterpretResult
		{
			Ok,
			CompileError,
			RuntimeError,
		};

		InterpretResult interpret(Chunk &chunk)
		{
			m_chunk = &chunk;
			m_ip = m_chunk->getFirstOp();

			for(;;)
			{
				uint8_t operation;
				switch (operation = *m_ip++)
				{
				case OP_NOP:
					break;
				case OP_RET:
					return InterpretResult::Ok;
				case OP_CONST:
					{
						BaseObject *value = m_chunk->getConstant(*m_ip++);
						value->toString();
					}
					break;
				}
			}

			return InterpretResult::Ok;
		}
	};
}

#endif // DVM_VIRTUALMACHINE_HPP
