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

	template<typename... Ts>
	constexpr bool IsByte = ((std::is_same_v<Ts, uint8_t> || std::is_same_v<Ts, vm::OpCode>) && ...); 

	class Compiler
	{
	private:
		Lexer m_lexer;
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

		void compile()
		{
			while (!m_lexer.isEnd())
			{
				Token token = m_lexer.getNextToken();
			}
		}

		template<typename... Ts>
		void emitBytes(Ts &&...args) requires IsByte<Ts...>
		{
			(m_chunk.write(args), ...);
		}
	};
}

#endif // DVM_COMPILER_HPP
