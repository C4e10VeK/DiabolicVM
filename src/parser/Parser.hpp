#ifndef DVM_PARSER_HPP
#define DVM_PARSER_HPP

#include <vector>
#include "Lexer.hpp"
#include "ast/ASTreeNodeBase.hpp"

namespace dialang
{
    class Parser
    {
    private:
        Lexer m_lexer;
        Token m_current;
        Token m_prev;
    public:

        Parser() = default;
        Parser(std::string code);

        void setSourceCode(const std::string &code);
		std::vector<ASTreeNode> parse();

	private:
		void advance();
		void consume(TokenType type);

		ASTreeNode parseStatement();
		ASTreeNode parseExpression();
		ASTreeNode parseUnary();
		ASTreeNode parseFactor();
		ASTreeNode parseTerm();

		ASTreeNode parseVarDecl();
    };
}

#endif // DVM_PARSER_HPP
