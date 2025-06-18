#include "tcalc/ast/binaryop.hpp"

namespace tcalc::ast {

BinaryOpNode::BinaryOpNode(NodeType type)
  : BinaryOpNode{ type, nullptr, nullptr }
{
}

BinaryOpNode::BinaryOpNode(NodeType type, NodePtr<> left, NodePtr<> right)
  : Node{ type }
  , _left{ std::move(left) }
  , _right{ std::move(right) }
{
}

}
