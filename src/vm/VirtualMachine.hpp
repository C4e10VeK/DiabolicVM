#ifndef DVM_VIRTUALMACHINE_HPP
#define DVM_VIRTUALMACHINE_HPP

#include <iostream>
#include <variant>
#include <vector>
#include <stack>
#include <string>
#include "OpCodes.hpp"
#include "Value.hpp"

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

	enum class InterpretResult
	{
		Ok,
		CompileError,
		RuntimeError,
	};

	class VM
	{
	private:
		Chunk *m_chunk;
		uint8_t *m_ip;
		std::stack<Value> m_stack;
	public:

		InterpretResult interpret(Chunk &chunk)
		{
			m_chunk = &chunk;
			m_ip = m_chunk->getFirstOp();

	#define BIN_OP(op) {Value b = m_stack.top(); \
						m_stack.pop(); \
						Value a = m_stack.top(); \
						m_stack.pop(); \
						if (!a.isAny<int32_t>() && !b.isAny<int32_t>()) \
							return InterpretResult::RuntimeError; \
						m_stack.push(a.as<int32_t>() op b.as<int32_t>());}

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

						if (a.is<std::string>() && b.is<std::string>())
						{
							m_stack.push(a.as<std::string>() + b.as<std::string>());
							break;
						}

						if (!a.isAny<int32_t>() && !b.isAny<int32_t>()) 
						{
							return InterpretResult::RuntimeError;
						}
						
						m_stack.push(a.as<int32_t>() + b.as<int32_t>());
					}
					break;
				case OP_SUB: BIN_OP(-)
					break;
				case OP_MUL: BIN_OP(*)
					break;
				case OP_DIV: BIN_OP(/)
					break;
				case OP_NEG:
					{
						Value val = m_stack.top();
						m_stack.pop();
						if (!val.isAny<int32_t>())
						{
							return InterpretResult::RuntimeError;
						}

						m_stack.push(-val.as<int32_t>());
					}
					break;
				case OP_PRINT:
					{
						Value a = m_stack.top();
						m_stack.pop();
						a.print();
						std::cout << std::endl;
					}
					break;
				default:
					std::cerr << "Unknown operation!" << std::endl;
					return InterpretResult::RuntimeError;
				}
			}

		#undef BIN_OP

			return InterpretResult::Ok;
		}
	};
}

#endif // DVM_VIRTUALMACHINE_HPP
