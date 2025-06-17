#include <utility>

#include "tcalc/ast/control_flow.hpp"

namespace tcalc::ast {

IfNode::IfNode()
  : IfNode{ nullptr, nullptr, nullptr }
{
}

IfNode::IfNode(std::shared_ptr<Node> cond,
               std::shared_ptr<Node> then,
               std::shared_ptr<Node> else_)
  : Node{ NodeType::IF }
  , _cond{ std::move(cond) }
  , _then{ std::move(then) }
  , _else{ std::move(else_) }
{
}

}
