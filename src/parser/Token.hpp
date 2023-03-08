#ifndef DVM_TOKEN_HPP
#define  DVM_TOKEN_HPP

#include <cstdint>
#include <utility>
#include <string>

namespace dialang
{
	enum TokenType
	{
		TOKEN_NONE = -1,

		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_LBRACE,
		TOKEN_RBRACE,
		TOKEN_PLUS,
		TOKEN_MINUS,
		TOKEN_STAR,
		TOKEN_SLASH,
		TOKEN_COLON,
		TOKEN_EQUAL,
		TOKEN_EQUAL_EQUAL,
		TOKEN_SEMICOLON,
		TOKEN_DOT,

		TOKEN_CONST,
		TOKEN_LET,
		TOKEN_FUNCTION,
		TOKEN_RETURN,

		TOKEN_NUMBER,
		TOKEN_STRING,
		TOKEN_NULL,
		
		TOKEN_ID,
		TOKEN_EOF
	};

	struct Token
	{
		std::string value;
		TokenType type;

		inline Token() = default;
		inline Token(std::string value_, TokenType type_) : value(std::move(value_)), type(type_) {}
	};
}

#endif // DVM_TOKEN_HPP
