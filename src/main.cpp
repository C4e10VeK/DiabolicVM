#include "vm/VirtualMachine.hpp"

int main()
{

	std::vector<uint8_t> bc = {
		dialang::vm::OP_LOAD, dialang::vm::TYPE_STRING, 'h', 'e', 'l', 'l', 'o', '!', '\0', // push "hello"
		dialang::vm::OP_CALL, 'p', 'r', 'i', 'n', 't', 'l', 'n', '\0', 						// call println
		dialang::vm::OP_RET 																// ret
	};

	auto a = dialang::vm::exec(bc);

	return 0;
}
