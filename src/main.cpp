#include "vm/VirtualMachine.hpp"

int main()
{
	dialang::vm::Chunk chunk;

	auto intval = new dialang::vm::I32Object();
	intval->value_ = 12;
	int32_t contId = chunk.addConstant(intval);
	chunk.write(dialang::vm::OP_CONST);
	chunk.write(contId);
	chunk.write(dialang::vm::OP_RET);

	return 0;
}
