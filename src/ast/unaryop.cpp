#include <utility>

#include "tcalc/ast/unaryop.hpp"

namespace tcalc::ast {

UnaryOpNode::UnaryOpNode(NodeType type)
  : UnaryOpNode{ type, nullptr }
{
}

UnaryOpNode::UnaryOpNode(NodeType type, NodePtr<> operand)
  : Node{ type }
  , _operand{ std::move(operand) }
{
}

}
