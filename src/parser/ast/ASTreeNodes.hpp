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
	public:

		ASTreeBinNode() : ASTreeNodeBase(ASTreeNodeType::Bin) { }

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
	public:

		ASTreeUnNode() : ASTreeNodeBase(ASTreeNodeType::Un) { }

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

	class ASTreeVarDeclNode : public ASTreeNodeBase
	{
	private:
		Token m_token;
	public:

		ASTreeVarDeclNode() : ASTreeNodeBase(ASTreeNodeType::Const) { }

		void analyze() override
		{
			
		}

		void compile() override
		{

		}

	};
}

#endif // DVM_ASTREENODES_HPP