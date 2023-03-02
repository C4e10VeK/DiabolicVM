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
		std::size_t m_pos;
	public:
		Lexer() = default;
		Lexer(std::string code);

		Token getNextToken();

		bool isEnd() const;

	private:
		void skipWhiteSpace();
	};

}

#endif // DVM_LEXER_HPP
