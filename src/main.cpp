#include "vm/VirtualMachine.hpp"
#include "vm/OpCodes.hpp"
#include "vm/Compiler.hpp"
#include "parser/Parser.hpp"
#include "utils.hpp"

int main()
{
	dialang::Parser parser;

	std::string code;

	if (!dialang::utils::readFile("../res/locals.dia", code))
	{
		return 1;
	}
	dialang::Compiler compiler(code);
	auto res = compiler.compile();

	dialang::vm::VM vm;
	vm.interpret(res);

	return 0;
}
