#ifndef DVM_ASTREENODEBASE_HPP
#define DVM_ASTREENODEBASE_HPP

#include <memory>

namespace dialang
{
    enum class ASTreeNodeType
    {
        
    };

    class ASTreeNodeBase : public std::enable_shared_from_this<ASTreeNodeBase>
    {

    };

    using ASTreeNode = std::shared_ptr<ASTreeNodeBase>;
}

#endif // DVM_ASTREENODEBASE_HPP