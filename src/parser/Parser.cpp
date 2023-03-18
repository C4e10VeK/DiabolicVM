#include "Parser.hpp"
#include <unordered_map>
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
		std::vector<ASTreeNode> program;
		while (!m_lexer.isEnd())
		{
			program.emplace_back(parseStatement());
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

	ASTreeNode Parser::parseStatement()
	{
		switch (m_current.type)
		{
		case TOKEN_LET:
			return parseVarDecl();
		default:
			break;
		}
		return {};
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
				res = makeNode<ASTreeUnNode>(res, token);
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

			res = makeNode<ASTreeBinNode>(res, parseUnary(), token);
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

			res = makeNode<ASTreeBinNode>(res, parseFactor(), token);
		}

		return res;
	}

	ASTreeNode Parser::parseVarDecl()
	{
		const std::unordered_map<std::string, VarType> strsTypes = {
			{"i32", VarType::Integer32},
			{"bool", VarType::Boolean},
			{"string", VarType::String}
		};
		

		consume(TOKEN_LET);
		Token id = m_current;
		consume(TOKEN_ID);
	
		VarType type = VarType::Integer32;

		if (m_current.type == TOKEN_COLON)
		{
			consume(TOKEN_COLON);
			if (!strsTypes.contains(m_current.value))
			{

			}
			else
			{
				type = strsTypes.at(m_current.value);
			}

			consume(TOKEN_ID);
		}


		return makeNode<ASTreeVarDeclNode>(id, type, parseExpression());
	}

}
