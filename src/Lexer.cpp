#include "Lexer.hpp"

namespace dialang::vm
{
	static inline bool isSpace(char c)
	{
		switch (c)
		{
		case ' ':
		case '\f':
		case '\n':
		case '\r':
		case '\t':
		case '\v':
			return true;
		default:
			break;
		}

		return false;
	}

	static inline bool isDigit(char c)
	{
		return c >= '0' && c <= '9';
	}

	static inline bool isLetter(char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}


	Lexer::Lexer(std::string code)
		: m_code(std::move(code)),
		  m_pos(0)
	{}

	Token Lexer::getNextToken()
	{
		skipWhiteSpace();

		return {"", TokenType::None};
	}

	bool Lexer::isEnd() const
	{
		return m_pos >= m_code.size();
	}

	void Lexer::skipWhiteSpace()
	{
		while (isSpace(m_code[m_pos]))
			++m_pos;
	}

}
