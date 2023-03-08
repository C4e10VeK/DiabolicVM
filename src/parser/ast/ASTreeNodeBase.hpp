#ifndef DVM_ASTREENODEBASE_HPP
#define DVM_ASTREENODEBASE_HPP

#include <memory>

namespace dialang
{
	class ASTreeNodeBase;

	template<typename T>
	concept IsASTreeNode = std::is_base_of_v<ASTreeNodeBase, T>;

	enum class ASTreeNodeType : int8_t
	{
		None = -1,
		Bin,
		Un,
		VarDecl,
		Number
	};

	class ASTreeNodeBase : public std::enable_shared_from_this<ASTreeNodeBase>
	{
	private:
		ASTreeNodeType m_type;
	public:
		ASTreeNodeBase() = default;
		ASTreeNodeBase(ASTreeNodeType type) : m_type(type) { }
		virtual ~ASTreeNodeBase() = default;

		inline ASTreeNodeType getType() const { return m_type; }

		virtual void compile() = 0;
		virtual void analyze() = 0;
	};

	using ASTreeNode = std::shared_ptr<ASTreeNodeBase>;
}

#endif // DVM_ASTREENODEBASE_HPP
