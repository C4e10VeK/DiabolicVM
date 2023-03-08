#include "Parser.hpp"
#include "ast/ASTreeNodes.hpp"

namespace dialang
{
    Parser::Parser(std::string code) : m_lexer(std::move(code)) { }

    void Parser::setSourceCode(const std::string &code)
    {
        m_lexer.setCode(code);
    }

	std::vector<ASTreeNode> Parser::parse()
	{
		while (!m_lexer.isEnd())
		{

		}

		return {};
	}

	void Parser::advance()
	{
		m_prev = m_current;
		m_current = m_lexer.getNextToken();
	}

	void Parser::consume(TokenType type)
	{
		if (m_current.type == type)
			advance();
	}

	ASTreeNode Parser::parseExpression()
	{
		return {};
	}

	ASTreeNode Parser::parseUnary()
	{
		Token token = m_current;

		ASTreeNode res = parseExpression();

		switch (token.type)
		{
		case TOKEN_MINUS:
			{
				consume(TOKEN_MINUS);
				res = std::make_shared<ASTreeUnNode>(res, token);
			}
		default:
			break;
		}

		return res;
	}

	ASTreeNode Parser::parseFactor()
	{
		ASTreeNode res = parseUnary();

		while (m_current.type == TOKEN_STAR || m_current.type == TOKEN_SLASH)
		{
			Token token = m_current;
			consume(token.type);

			res = std::make_shared<ASTreeBinNode>(res, parseUnary(), token);
		}

		return res;
	}

	ASTreeNode Parser::parseTerm()
	{
		ASTreeNode res = parseFactor();

		while (m_current.type == TOKEN_PLUS || m_current.type == TOKEN_MINUS)
		{
			Token token = m_current;
			consume(token.type);

			res = std::make_shared<ASTreeBinNode>(res, parseFactor(), token);
		}

		return res;
	}

}
