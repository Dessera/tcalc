#include "tcalc/ast/variable.hpp"

namespace tcalc::ast {

VarRefNode::VarRefNode(std::string name)
  : Node{ NodeType::VARREF }
  , _name{ std::move(name) }
{
}

VarAssignNode::VarAssignNode(std::string name)
  : VarAssignNode{ std::move(name), nullptr }
{
}

VarAssignNode::VarAssignNode(std::string name, NodePtr<> body)
  : Node{ NodeType::VARASSIGN }
  , _name{ std::move(name) }
  , _body{ std::move(body) }
{
}

}
