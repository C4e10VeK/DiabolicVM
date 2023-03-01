#include "vm/VirtualMachine.hpp"
#include "vm/OpCodes.hpp"

int main()
{
	dialang::vm::Chunk chunk;

	int32_t constStrId = chunk.addConstant("Hello world!");
	chunk.write(dialang::vm::OP_CONST);
	chunk.write(constStrId);

	constStrId = chunk.addConstant("Anton");
	chunk.write(dialang::vm::OP_CONST);
	chunk.write(constStrId);

	chunk.write(dialang::vm::OP_ADD);

	chunk.write(dialang::vm::OP_RET);

	dialang::vm::VM vm;
	vm.interpret(chunk);

	return 0;
}
