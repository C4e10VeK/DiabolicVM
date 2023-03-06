#ifndef DVM_COMPILER_HPP
#define DVM_COMPILER_HPP

#include <filesystem>
#include <fstream>
#include <cstdint>
#include <type_traits>
#include "OpCodes.hpp"
#include "VirtualMachine.hpp"
#include "../parser/Lexer.hpp"

namespace dialang
{

	class Compiler
	{
	private:
		Lexer m_lexer;
		Token m_token;
		vm::Chunk m_chunk;
	public:
		Compiler() = default;
		Compiler(std::string code) : m_lexer(std::move(code)) { }

		bool openFile(const std::filesystem::path &path)
		{
			std::ifstream f;
			std::string text;
			
			if (!std::filesystem::exists(path))
				return false;

			f.open(path, std::ios::binary);

			if (!f.is_open())
				return false;
			
			f.seekg(0, std::ios::end);
			text.reserve(f.tellg());
			f.seekg(0, std::ios::beg);

			text.assign((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

			f.close();

			m_lexer.setCode(text);

			return true;
		}

		vm::InterpretResult compile()
		{
			while (!m_lexer.isEnd())
			{
				m_token = m_lexer.getNextToken();
			}

			return vm::InterpretResult::CompileOk;
		}

	private:

		vm::InterpretResult compileExpr()
		{
			return vm::InterpretResult::CompileOk;
		}

		vm::InterpretResult consume(TokenType type)
		{
			if (m_token.type == type)
			{
				return vm::InterpretResult::CompileError;
			}

			m_token = m_lexer.getNextToken();
			return vm::InterpretResult::CompileOk;
		}

		template<typename... Ts>
		void emitBytes(Ts &&...args)
		{
			(m_chunk.write(args), ...);
		}
	};
}

#endif // DVM_COMPILER_HPP
