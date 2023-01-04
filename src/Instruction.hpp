#ifndef DVM_INSTRUCTION_HPP
#define DVM_INSTRUCTION_HPP

#include <cstdint>

namespace dialang::vm
{
	enum OpCodes : uint8_t
	{
		OP_NOP,
		OP_RET,
		OP_RETV,
		OP_LOAD,	
		OP_LOADA,
		OP_LOADAC,
		OP_CALL,

		OPS_COUNT
	};

	enum Registers : uint8_t
	{
		R_ACC,
		R_R0,
		R_R1,
		R_R2,
		R_R3,
		R_SP,
		R_IP,

		REGISTERS_COUNT
	};

	enum DiaBcTypes : uint8_t
	{
		TYPE_BYTE,
		TYPE_WORD,
		TYPE_DWORD,
		TYPE_QWORD,
		TYPE_STRING,

		TYPES_COUNT
	};
}

#endif // DVM_INSTRUCTION_HPP
