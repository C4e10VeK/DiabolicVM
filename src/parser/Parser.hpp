#ifndef DVM_PARSER_HPP
#define DVM_PARSER_HPP

#include "Lexer.hpp"
#include "ast/ASTreeNodeBase.hpp"

namespace dialang
{
	class Parser
	{
	private:
		Lexer m_lexer;
	public:
		Parser() = default;
		Parser(std::string code);

		void setCode(const std::string &code);

		ASTreeNode parse();
	};
}

#endif // DVM_PARSER_HPP
