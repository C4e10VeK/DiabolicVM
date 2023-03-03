#include "Parser.hpp"

namespace dialang
{
	Parser::Parser(std::string code) : m_lexer(std::move(code)) { }

	void Parser::setCode(const std::string &code)
	{
		m_lexer.setCode(code);
	}

	ASTreeNode Parser::parse()
	{
		

		return {};
	}
}