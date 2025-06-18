#include <utility>

#include "tcalc/ast/control_flow.hpp"

namespace tcalc::ast {

IfNode::IfNode()
  : IfNode{ nullptr, nullptr, nullptr }
{
}

IfNode::IfNode(NodePtr<> cond, NodePtr<> then, NodePtr<> else_)
  : Node{ NodeType::IF }
  , _cond{ std::move(cond) }
  , _then{ std::move(then) }
  , _else{ std::move(else_) }
{
}

}
