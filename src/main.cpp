#include "vm/VirtualMachine.hpp"
#include "vm/OpCodes.hpp"

int main()
{
	dialang::vm::Chunk chunk;

	dialang::vm::I32Object intval;
	intval.value_ = 12;
	int32_t constId = chunk.addConstant(intval);
	chunk.write(dialang::vm::OP_CONST);
	chunk.write(constId);
	chunk.write(dialang::vm::OP_RET);

	dialang::vm::VM vm;
	vm.interpret(chunk);

	return 0;
}
