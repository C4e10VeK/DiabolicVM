#include "vm/VirtualMachine.hpp"
#include "vm/OpCodes.hpp"

int main()
{
	dialang::vm::Chunk chunk;

	int32_t constId = chunk.addConstant("Hello world!");
	chunk.write(dialang::vm::OP_CONST);
	chunk.write(constId);

	constId = chunk.addConstant(" Hello streamer!");
	chunk.write(dialang::vm::OP_CONST);
	chunk.write(constId);

	chunk.write(dialang::vm::OP_CONCAT);

	chunk.write(dialang::vm::OP_PRINT);

	chunk.write(dialang::vm::OP_RET);

	dialang::vm::VM vm;
	vm.interpret(chunk);

	return 0;
}
