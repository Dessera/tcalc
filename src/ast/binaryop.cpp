#include "tcalc/ast/binaryop.hpp"

namespace tcalc::ast {

BinaryOpNode::BinaryOpNode(NodeType type)
  : BinaryOpNode{ type, nullptr, nullptr }
{
}

BinaryOpNode::BinaryOpNode(NodeType type,
                           std::shared_ptr<Node> left,
                           std::shared_ptr<Node> right)
  : Node{ type }
  , _left{ std::move(left) }
  , _right{ std::move(right) }
{
}

}
