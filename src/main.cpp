#include "vm/VirtualMachine.hpp"
#include "vm/OpCodes.hpp"

int main()
{
	dialang::vm::Chunk chunk;

	int32_t constId = chunk.addConstant(10);
	chunk.write(dialang::vm::OP_CONST);
	chunk.write(constId);

	chunk.write(dialang::vm::OP_PRINT);

	chunk.write(dialang::vm::OP_RET);

	dialang::vm::VM vm;
	vm.interpret(chunk);

	return 0;
}
