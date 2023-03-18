#include "vm/VirtualMachine.hpp"
#include "vm/OpCodes.hpp"
#include "parser/Lexer.hpp"

int main()
{
	dialang::Lexer lexer;

	lexer.setCode(dialang::utils::readFile("../res/globals.dia"));
	std::vector<dialang::Token> tokens;

	while (!lexer.isEnd())
	{
		tokens.emplace_back(lexer.getNextToken());
	}

	// dialang::vm::Chunk chunk;

	// int32_t constId = chunk.addConstant(10);
	// chunk.write(dialang::vm::OP_PUSHC);
	// chunk.write(constId);

	// chunk.write(dialang::vm::OP_PRINT);

	// chunk.write(dialang::vm::OP_RET);

	// dialang::vm::VM vm;
	// vm.interpret(chunk);

	return 0;
}
