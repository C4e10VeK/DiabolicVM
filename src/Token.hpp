#ifndef DVM_TOKEN_HPP
#define  DVM_TOKEN_HPP

#include <cstdint>
#include <utility>
#include <string>

namespace dialang::vm
{
	enum class TokenType
	{
		None = -1,
		Operation,
		FuncDeclaration,
		Constant,
		ValType,
		Value,
	};

	struct Token
	{
		std::string value;
		TokenType type;

		inline Token() = default;
		inline Token(std::string _value, TokenType _type) : value(std::move(_value)), type(_type) {}
	};
}

#endif // DVM_TOKEN_HPP
