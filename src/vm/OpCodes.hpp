#ifndef DVM_INSTRUCTION_HPP
#define DVM_INSTRUCTION_HPP

#include <cstdint>

namespace dialang::vm
{
	enum OpCodes : uint8_t
	{
		OP_NOP,
		OP_RET,
		OP_CONST,
		OP_PUSH,
		OP_MOVC,
		OP_ADD,	
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_INC,
		OP_DEC,
		OP_CALL,

		OPS_COUNT
	};
}

#endif // DVM_INSTRUCTION_HPP
