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
		advance();
		while (!m_lexer.isEnd())
		{
			program.emplace_back(parseStatement());
		}

		return program;
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
		case TOKEN_PRINT:
			return parsePrintStm();
		case TOKEN_LBRACE:
			return parseBlock();
		default:
			return parseExpression();
		}
		return {};
	}

	ASTreeNode Parser::parseExpression()
	{
		return parseTerm();
	}

	ASTreeNode Parser::parseUnary()
	{
		Token token = m_current;

		ASTreeNode res;

		switch (token.type)
		{
		case TOKEN_LPAREN:
			{
				consume(TOKEN_LPAREN);
				res = parseExpression();
				consume(TOKEN_RPAREN);
			}
			break;
		case TOKEN_MINUS:
			{
				consume(TOKEN_MINUS);
				res = makeNode<ASTreeUnNode>(parseExpression(), token);
			}
			break;
		case TOKEN_NUMBER:
			{
				consume(TOKEN_NUMBER);
				res = makeNode<ASTreeConstValNode>(token);
			}
			break;
		case TOKEN_STRING:
			{
				consume(TOKEN_STRING);
				res = makeNode<ASTreeConstValNode>(token);
			}
			break;
		case TOKEN_ID:
			{
				consume(TOKEN_ID);
				res = makeNode<ASTreeVarNode>(token);
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
			{"f32", VarType::Float},
			{"f64", VarType::Double},
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

		if (m_current.type != TOKEN_EQUAL)
			return makeNode<ASTreeVarDeclNode>(id, type, ASTreeNode());
			
		consume(TOKEN_EQUAL);

		return makeNode<ASTreeVarDeclNode>(id, type, parseExpression());
	}

	ASTreeNode Parser::parseGetVar()
	{
		Token id = m_current;
		consume(TOKEN_ID);

		return makeNode<ASTreeVarNode>(id);
	}

	ASTreeNode Parser::parsePrintStm()
	{
		consume(TOKEN_PRINT);
		return  makeNode<ASTreePrintStmNode>(parseExpression());
	}

	ASTreeNode Parser::parseBlock()
	{
		consume(TOKEN_LBRACE);

		std::vector<ASTreeNode> nodes;
		while (!m_lexer.isEnd() && m_current.type != TOKEN_RBRACE)
		{
			nodes.emplace_back(parseStatement());
		}

		consume(TOKEN_RBRACE);

		return makeNode<ASTreeBlockNode>(nodes);
	}

}
