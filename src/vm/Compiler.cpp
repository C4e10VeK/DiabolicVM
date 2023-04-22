#include "Compiler.hpp"
#include "../utils.hpp"

namespace dialang
{
	Compiler::Compiler(std::string code) : m_parser(std::move(code)) { }

	bool Compiler::openFile(const std::filesystem::path &path)
	{
		std::string text;
		bool res = utils::readFile(path, text);

		m_parser.setSourceCode(text);

		return res;
	}

	vm::Chunk Compiler::compile()
	{
		auto res = m_parser.parse();

		for (const auto &node : res)
		{
			node->take(*this);
		}

		emitBytes(vm::OP_RET);
		return m_chunk;
	}

	void Compiler::emitConstant(vm::Value value)
	{
		uint8_t constId = m_chunk.addConstant(value);
		emitBytes(vm::OP_PUSHC, constId);
	}

	uint8_t Compiler::emitIdConst(const std::string &id)
	{
		return m_chunk.addConstant({id});
	}

	void Compiler::beginBlock()
	{

	}

	void Compiler::endBlock()
	{
		
	}

	void Compiler::setState(CompileState state)
	{
		m_state = state;
	}

	CompileState &Compiler::getState()
	{
		return m_state;
	}
}