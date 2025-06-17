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

BinaryPlusNode::BinaryPlusNode()
  : BinaryOpNode{ NodeType::BINARY_PLUS }
{
}

BinaryPlusNode::BinaryPlusNode(std::shared_ptr<Node> left,
                               std::shared_ptr<Node> right)
  : BinaryOpNode{ NodeType::BINARY_PLUS, std::move(left), std::move(right) }
{
}

BinaryMinusNode::BinaryMinusNode()
  : BinaryOpNode{ NodeType::BINARY_MINUS }
{
}

BinaryMinusNode::BinaryMinusNode(std::shared_ptr<Node> left,
                                 std::shared_ptr<Node> right)
  : BinaryOpNode{ NodeType::BINARY_MINUS, std::move(left), std::move(right) }
{
}

BinaryMultiplyNode::BinaryMultiplyNode()
  : BinaryOpNode{ NodeType::BINARY_MULTIPLY }
{
}

BinaryMultiplyNode::BinaryMultiplyNode(std::shared_ptr<Node> left,
                                       std::shared_ptr<Node> right)
  : BinaryOpNode{ NodeType::BINARY_MULTIPLY, std::move(left), std::move(right) }
{
}

BinaryDivideNode::BinaryDivideNode()
  : BinaryOpNode{ NodeType::BINARY_DIVIDE }
{
}

BinaryDivideNode::BinaryDivideNode(std::shared_ptr<Node> left,
                                   std::shared_ptr<Node> right)
  : BinaryOpNode{ NodeType::BINARY_DIVIDE, std::move(left), std::move(right) }
{
}

BinaryEqualNode::BinaryEqualNode()
  : BinaryOpNode{ NodeType::BINARY_EQUAL }
{
}

BinaryEqualNode::BinaryEqualNode(std::shared_ptr<Node> left,
                                 std::shared_ptr<Node> right)
  : BinaryOpNode{ NodeType::BINARY_EQUAL, std::move(left), std::move(right) }
{
}

BinaryNotEqualNode::BinaryNotEqualNode()
  : BinaryOpNode{ NodeType::BINARY_NOT_EQUAL }
{
}

BinaryNotEqualNode::BinaryNotEqualNode(std::shared_ptr<Node> left,
                                       std::shared_ptr<Node> right)
  : BinaryOpNode{ NodeType::BINARY_NOT_EQUAL,
                  std::move(left),
                  std::move(right) }
{
}

BinaryGreaterNode::BinaryGreaterNode()
  : BinaryOpNode{ NodeType::BINARY_GREATER }
{
}

BinaryGreaterNode::BinaryGreaterNode(std::shared_ptr<Node> left,
                                     std::shared_ptr<Node> right)
  : BinaryOpNode{ NodeType::BINARY_GREATER, std::move(left), std::move(right) }
{
}

BinaryGreaterEqualNode::BinaryGreaterEqualNode()
  : BinaryOpNode{ NodeType::BINARY_GREATER_EQUAL }
{
}

BinaryGreaterEqualNode::BinaryGreaterEqualNode(std::shared_ptr<Node> left,
                                               std::shared_ptr<Node> right)
  : BinaryOpNode{ NodeType::BINARY_GREATER_EQUAL,
                  std::move(left),
                  std::move(right) }
{
}

BinaryLessNode::BinaryLessNode()
  : BinaryOpNode{ NodeType::BINARY_LESS }
{
}

BinaryLessNode::BinaryLessNode(std::shared_ptr<Node> left,
                               std::shared_ptr<Node> right)
  : BinaryOpNode{ NodeType::BINARY_LESS, std::move(left), std::move(right) }
{
}

BinaryLessEqualNode::BinaryLessEqualNode()
  : BinaryOpNode{ NodeType::BINARY_LESS_EQUAL }
{
}

BinaryLessEqualNode::BinaryLessEqualNode(std::shared_ptr<Node> left,
                                         std::shared_ptr<Node> right)
  : BinaryOpNode{ NodeType::BINARY_LESS_EQUAL,
                  std::move(left),
                  std::move(right) }
{
}

}
