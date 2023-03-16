#ifndef DVM_ASTREENODES_HPP
#define DVM_ASTREENODES_HPP

#include <variant>
#include "ASTreeNodeBase.hpp"
#include "../Token.hpp"

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
		
		void analyze() override
		{

		}

		void compile() override
		{

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

		void analyze() override
		{
			
		}

		void compile() override
		{

		}
	};

	class ASTreeNumberNode : public ASTreeNodeBase
	{
	private:
		Token m_number;
	public:
		ASTreeNumberNode() = default;
		ASTreeNumberNode(Token token) : m_number(token) { }

		void analyze() override
		{

		}

		void compile() override
		{

		}
	};

	enum class VarType
	{
		Integer32,
		Boolean,
		String
	};

	class ASTreeVarDeclNode : public ASTreeNodeBase
	{
	private:
		Token m_token;
		VarType m_type;
		ASTreeNode m_init;
	public:

		ASTreeVarDeclNode() : ASTreeNodeBase(ASTreeNodeType::VarDecl) { }
		ASTreeVarDeclNode(Token token, VarType type)
			: ASTreeNodeBase(ASTreeNodeType::VarDecl),
			  m_token(token),
			  m_type(type) { }

		void analyze() override
		{
			
		}

		void compile() override
		{

		}

	};
}

#endif // DVM_ASTREENODES_HPP
