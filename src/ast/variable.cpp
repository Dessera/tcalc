#include "tcalc/ast/variable.hpp"

namespace tcalc::ast {

VariableNode::VariableNode(std::string name)
  : Node{ NodeType::VARIABLE }
  , _name{ std::move(name) }
{
}

}
