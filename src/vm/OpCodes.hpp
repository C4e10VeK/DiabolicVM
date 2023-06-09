#ifndef DVM_INSTRUCTION_HPP
#define DVM_INSTRUCTION_HPP

#include <cstdint>

namespace dialang::vm
{
	enum OpCode : uint8_t
	{
		OP_NOP,
		OP_RET,
		OP_PUSHC,
		OP_PUSHI,
		OP_POP,
		OP_GETG,
		OP_SETG,
		OP_GETL,
		OP_SETL,
		OP_ADD,
		OP_ADDI,	
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_INC,
		OP_DEC,
		OP_NEG,
		OP_CONCAT,
		
		// TODO: realize function print
		OP_PRINT,

		OPS_COUNT
	};

	constexpr uint8_t CONST_BLOCK_BEGIN = OPS_COUNT + 1;
	constexpr uint8_t CONST_BLOCK_END = CONST_BLOCK_BEGIN + 1;
}

#endif // DVM_INSTRUCTION_HPP
