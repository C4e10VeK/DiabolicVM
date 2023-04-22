#ifndef DVM_ASTREENODES_HPP
#define DVM_ASTREENODES_HPP

#include <type_traits>
#include <variant>
#include "ASTreeNodeBase.hpp"
#include "../Token.hpp"
#include "../../vm/Compiler.hpp"

namespace dialang
{
	class ASTreeBinNode : public ASTreeNodeBase
	{
	private:
		ASTreeNode m_left;
		ASTreeNode m_right;
		Token m_name;
	public:

		ASTreeBinNode() : ASTreeNodeBase(ASTreeNodeType::Bin) { }
		ASTreeBinNode(ASTreeNode left, ASTreeNode right, Token token)
			: ASTreeNodeBase(ASTreeNodeType::Bin),
			  m_left(left),
			  m_right(right),
			  m_name(token) { }

		ASTreeNode getLeft() const
		{
			return m_left;
		}

		ASTreeNode getRight() const
		{
			return m_right;
		}
		
		void take(Compiler &compiler) override
		{
			m_left->take(compiler);
			m_right->take(compiler);

			switch (m_name.type)
			{
			case TOKEN_PLUS:
				compiler.emitBytes(vm::OP_ADD);
				break;
			case TOKEN_MINUS:
				compiler.emitBytes(vm::OP_SUB);
				break;
			case TOKEN_STAR:
				compiler.emitBytes(vm::OP_MUL);
				break;
			case TOKEN_SLASH:
				compiler.emitBytes(vm::OP_DIV);
			default:
				throw;
			}
		}
		
	};

	class ASTreeUnNode : public ASTreeNodeBase
	{
	private:
		ASTreeNode m_children;
		Token m_name;
	public:

		ASTreeUnNode() : ASTreeNodeBase(ASTreeNodeType::Un) { }
		ASTreeUnNode(ASTreeNode node, Token token)
			: ASTreeNodeBase(ASTreeNodeType::Un),
			  m_children(node),
			  m_name(token) { }

		ASTreeNode getChildren() const
		{
			return m_children;
		}

		void take(Compiler &compiler) override
		{
			m_children->take(compiler);
			compiler.emitBytes(vm::OP_NEG);
		}
	};

	class ASTreeConstValNode : public ASTreeNodeBase
	{
	private:
		Token m_const;
	public:
		ASTreeConstValNode() = default;
		ASTreeConstValNode(Token token)
			: ASTreeNodeBase(ASTreeNodeType::ConstVal),
			  m_const(token) { }

		void take(Compiler &compiler) override
		{
			switch (m_const.type)
			{
			case TOKEN_NUMBER:
			{
				if (m_const.value.find('.') != std::string::npos)
				{
					vm::dvm_float val = std::stod(m_const.value);
					compiler.emitConstant({val});
					break;
				}
				
				vm::dvm_int val = std::stoll(m_const.value);
				compiler.emitConstant({val});

				break;
			}
			case TOKEN_STRING:
			{
				compiler.emitConstant({m_const.value});
				break;
			}
			default:
				break;
			}
		}
	};

	class ASTreeVarDeclNode : public ASTreeNodeBase
	{
	private:
		Token m_token;
		VarType m_type;
		ASTreeNode m_init;
	public:

		ASTreeVarDeclNode() : ASTreeNodeBase(ASTreeNodeType::VarDecl) { }
		ASTreeVarDeclNode(Token token, VarType type, ASTreeNode init)
			: ASTreeNodeBase(ASTreeNodeType::VarDecl),
			  m_token(token),
			  m_type(type),
			  m_init(init)
		{ }

		void take(Compiler &compiler) override
		{
			if (m_init)
				m_init->take(compiler);
			
			uint8_t id = compiler.emitIdConst(m_token.value);
			compiler.emitBytes(vm::OP_SETG, id);
		}
	};

	class ASTreeVarNode : public ASTreeNodeBase
	{
	private:
		Token m_name;
	public:
		ASTreeVarNode() = default;
		ASTreeVarNode(Token token) : m_name(token) { }

		void take(Compiler &compiler) override
		{
			uint8_t id = compiler.emitIdConst(m_name.value);
			compiler.emitBytes(vm::OP_GETG, id);
		}
	};

	class ASTreePrintStmNode : public ASTreeNodeBase
	{
	private:
		ASTreeNode m_node;
	public:
		ASTreePrintStmNode(ASTreeNode node) : m_node(node) { }

		void take(Compiler &compiler) override
		{
			if (m_node)
				m_node->take(compiler);

			compiler.emitBytes(vm::OP_PRINT);
		}
	};

	template<IsASTreeNode Node, typename ...Args>
	inline ASTreeNode makeNode(Args ...args)
	{
		return std::make_shared<Node>(args...);
	}
}

#endif // DVM_ASTREENODES_HPP
