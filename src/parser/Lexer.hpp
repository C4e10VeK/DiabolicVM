#ifndef DVM_LEXER_HPP
#define DVM_LEXER_HPP

#include <string>
#include "Token.hpp"

namespace dialang
{

	class Lexer
	{
	private:
		std::string m_code;
		size_t m_pos;
		int32_t m_line;
	public:
		Lexer() = default;
		Lexer(std::string code);

		void setCode(const std::string &code);

		Token getNextToken();

		bool isEnd() const;

	private:
		void skipWhiteSpace();
		bool match(char c);
	};

}

#endif // DVM_LEXER_HPP
