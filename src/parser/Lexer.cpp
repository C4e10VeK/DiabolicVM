#include "Lexer.hpp"

namespace dialang
{
	static inline bool isSpace(char c)
	{
		switch (c)
		{
		case ' ':
		case '\f':
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
		  m_pos(0),
		  m_line(1)
	{}

	void Lexer::setCode(const std::string &code)
	{
		m_code = code;
		m_line = 1;
	}

	Token Lexer::getNextToken()
	{
		if (m_code[m_pos] == '\n')
		{
			++m_line;
			++m_pos;
		}

		skipWhiteSpace();

		if (isDigit(m_code[m_pos]))
		{
			std::string number;
			while (isDigit(m_code[m_pos]))
			{
				number.push_back(m_code[m_pos++]);
			}

			return Token(number, TOKEN_NUMBER);
		}

		switch (m_code[m_pos++])
		{
		case '+':
			return Token("+", TOKEN_PLUS);
		case '-':
			return Token("-", TOKEN_MINUS);
		case '*':
			return Token("*", TOKEN_STAR);
		case '/':
			return Token("/", TOKEN_SLASH);
		case '(':
			return Token("(", TOKEN_LPAREN);
		case ')':
			return Token(")", TOKEN_RPAREN);
		case '{':
			return Token("{", TOKEN_LBRACE);
		case '}':
			return Token("}", TOKEN_RBRACE);
		case ':':
			return Token(":", TOKEN_COLON);
		case '=':
			return Token("=", TOKEN_EQUAL);
		default:
			break;
		}

		return {"", TOKEN_NONE};
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
