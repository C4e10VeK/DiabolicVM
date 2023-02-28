#ifndef DVM_VIRTUALMACHINE_HPP
#define DVM_VIRTUALMACHINE_HPP

#include <iostream>
#include <stdint.h>
#include <vector>
#include <array>
#include <stack>
#include <string>
#include "OpCodes.hpp"
#include "Types.hpp"

namespace dialang::vm
{

	class Chunk
	{
	private:
		std::vector<Value> m_constants;
		std::vector<uint8_t> m_code;
	public:
		void write(uint8_t code)
		{
			m_code.emplace_back(code);
		}

		int32_t addConstant(Value value)
		{
			m_constants.emplace_back(value);
			return m_constants.size() - 1;
		}

		uint8_t *getFirstOp()
		{
			return &m_code[0];
		}

		Value getConstant(int32_t index)
		{
			return m_constants[index];
		}
	};

	class VM
	{
	private:
		Chunk *m_chunk;
		uint8_t *m_ip;
		std::stack<Value> m_stack;
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
					++m_ip;
					break;
				case OP_RET:
					return InterpretResult::Ok;
				case OP_CONST:
					{
						Value value = m_chunk->getConstant(*m_ip++);
						m_stack.push(value);
					}
					break;
				case OP_ADD:
					{
						Value b = m_stack.top();
						m_stack.pop();
						Value a = m_stack.top();
						m_stack.pop();

						if (a.type == ValueType::Number && b.type == ValueType::Number)
						{
							m_stack.push(a.as.int32 + b.as.int32);
						}
					}
					break;
				}
			}

			return InterpretResult::Ok;
		}
	};
}

#endif // DVM_VIRTUALMACHINE_HPP
