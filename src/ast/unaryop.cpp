#include <utility>

#include "tcalc/ast/unaryop.hpp"

namespace tcalc::ast {

UnaryOpNode::UnaryOpNode(NodeType type)
  : UnaryOpNode{ type, nullptr }
{
}

UnaryOpNode::UnaryOpNode(NodeType type, std::shared_ptr<Node> operand)
  : Node{ type }
  , _operand{ std::move(operand) }
{
}
UnaryPlusNode::UnaryPlusNode()
  : UnaryOpNode{ NodeType::UNARY_PLUS }
{
}

UnaryPlusNode::UnaryPlusNode(std::shared_ptr<Node> operand)
  : UnaryOpNode{ NodeType::UNARY_PLUS, std::move(operand) }
{
}

UnaryMinusNode::UnaryMinusNode()
  : UnaryOpNode{ NodeType::UNARY_MINUS }
{
}

UnaryMinusNode::UnaryMinusNode(std::shared_ptr<Node> operand)
  : UnaryOpNode{ NodeType::UNARY_MINUS, std::move(operand) }
{
}

}
