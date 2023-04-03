#include "Lexer.hpp"
#include <unordered_map>

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
		case '\n':
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
		m_pos = 0;
		m_line = 1;
	}

	Token Lexer::getNextToken()
	{
		skipWhiteSpace();

		if (isDigit(m_code[m_pos]))
		{
			return number();
		}

		if (isLetter(m_code[m_pos]))
		{
			return letter();
		}

		switch (m_code[m_pos++])
		{
		case '+':
			return Token("+", TOKEN_PLUS);
		case '-':
			{
				if (isDigit(m_code[m_pos]))
				{
					Token res = number();
					res.value = '-' + res.value;
					return res;
				}
				return Token("-", TOKEN_MINUS);
			}
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
			return match('=') ? Token("==", TOKEN_EQUAL_EQUAL)
								 : Token("=", TOKEN_EQUAL);
		case '.':
			return Token(".", TOKEN_DOT);
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

	Token Lexer::number()
	{
		std::string number;
		while (isDigit(m_code[m_pos]))
		{
			number.push_back(m_code[m_pos++]);
		}

		return Token(number, TOKEN_NUMBER);
	}

	Token Lexer::letter()
	{
		static const std::unordered_map<std::string, Token> keywords = {
			{"let", {"let", TOKEN_LET}},
			{"const", {"const", TOKEN_CONST}},
			{"fn", {"fn", TOKEN_FUNCTION}},
			{"return", {"return", TOKEN_RETURN}},
		};

		std::string letter;
		while (!isSpace(m_code[m_pos]) && isLetter(m_code[m_pos]) || isDigit(m_code[m_pos]))
		{
			letter.push_back(m_code[m_pos++]);
		}

		if (keywords.contains(letter))
			return keywords.at(letter);

		return Token(letter, TOKEN_ID);
	}

	bool Lexer::match(char c)
	{
		if (isEnd()) return false;
		if (m_code[m_pos] != c) return false;
		++m_pos;
		return true;
	}

}
