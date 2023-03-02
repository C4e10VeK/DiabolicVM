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
    };

    class ASTreeNodeBase : public std::enable_shared_from_this<ASTreeNodeBase>
    {
	public:
		virtual ~ASTreeNodeBase() = default;

		virtual void compile() = 0;
		virtual void analyze() = 0;
    };

    using ASTreeNode = std::shared_ptr<ASTreeNodeBase>;
}

#endif // DVM_ASTREENODEBASE_HPP
