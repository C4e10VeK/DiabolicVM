#include "VirtualMachine.hpp"

#include <cstring>
#include "OpCodes.hpp"

#define RUNTIME_ERROR(message) ({\
		std::cerr << message << std::endl; \
		dialang::vm::InterpretResult::RuntimeError;})

namespace dialang::vm
{
	InterpretResult VM::interpret(Chunk &chunk)
	{
		m_chunk = &chunk;
		m_ip = m_chunk->getFirstOp();

	#define BIN_OP(op) ({Value b = m_stack.pop(); \
						Value a = m_stack.pop(); \
						if (!a.isAny<int32_t>() && !b.isAny<int32_t>()){ \
							return RUNTIME_ERROR("Only number support "#op); \
						} \
						m_stack.push(a.as<int32_t>() op b.as<int32_t>());})

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
			case OP_PUSHC:
				{
					Value value = m_chunk->getConstant(*m_ip++);
					m_stack.push(value);
				}
				break;
			case OP_PUSHI:
				{
					int32_t value;
					std::memcpy(&value, m_ip, sizeof(int32_t));

					m_stack.push(value);

					m_ip += sizeof(int32_t);
				}
				break;
			case OP_GETG:
				{
					auto value = m_chunk->getConstant(*m_ip++);

					m_stack.push(m_globals[value.as<std::string>()]);
				}
				break;
			case OP_SETG:
				{
					auto value = m_chunk->getConstant(*m_ip++);

					m_globals[value.as<std::string>()] = m_stack.pop();
				}
				break;
			case OP_ADD: BIN_OP(+);	
				break;
			case OP_ADDI:
				{
					Value a = m_stack.pop();
					int32_t b;

					std::memcpy(&b, m_ip, sizeof(int32_t));
					m_stack.push(a.as<int32_t>() + b);

					m_ip += sizeof(int32_t);
				}
				break;
			case OP_SUB: BIN_OP(-);
				break;
			case OP_MUL: BIN_OP(*);
				break;
			case OP_DIV: BIN_OP(/);
				break;
			case OP_NEG:
				{
					Value val = m_stack.pop();
					if (!val.isAny<int32_t>())
					{
						return RUNTIME_ERROR("Only number support negative");
					}

					m_stack.push(-val.as<int32_t>());
				}
				break;
			case OP_CONCAT:
				{
					Value b = m_stack.pop();
					Value a = m_stack.pop();

					if (!a.is<std::string>() || !b.is<std::string>())
					{
						return RUNTIME_ERROR("Only string support concat");
					}
					m_stack.push(a.as<std::string>() + b.as<std::string>());
				}
				break;
			case OP_PRINT:
				{
					Value a = m_stack.pop();
					a.print();
					std::cout << std::endl;
				}
				break;
			default:
				return RUNTIME_ERROR("Unknown operation!");
			}
		}

	#undef BIN_OP

		return InterpretResult::Ok;
	}
}
