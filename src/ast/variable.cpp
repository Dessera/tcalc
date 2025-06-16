#include "tcalc/ast/variable.hpp"

namespace tcalc::ast {

VarRefNode::VarRefNode(std::string name)
  : Node{ NodeType::VARREF }
  , _name{ std::move(name) }
{
}

}
