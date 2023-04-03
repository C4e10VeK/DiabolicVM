#include "vm/VirtualMachine.hpp"
#include "vm/OpCodes.hpp"
#include "vm/Compiler.hpp"
#include "parser/Parser.hpp"
#include "utils.hpp"

int main()
{
	dialang::Parser parser;

	std::string code;

	if (!dialang::utils::readFile("../res/globals.dia", code))
	{
		return 1;
	}
	dialang::Compiler compiler(code);
	auto res = compiler.compile();



	// parser.setSourceCode(code);

	// auto res = parser.parse();

	// for (const auto &node : res)
	// {
	// 	node->take(compiler);
	// }

	// dialang::vm::Chunk chunk;

	// int32_t constId = chunk.addConstant(10);
	// chunk.write(dialang::vm::OP_PUSHC);
	// chunk.write(constId);

	// chunk.write(dialang::vm::OP_PRINT);

	// chunk.write(dialang::vm::OP_RET);

	dialang::vm::VM vm;
	vm.interpret(res);

	return 0;
}
