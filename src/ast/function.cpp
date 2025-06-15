#include "tcalc/ast/function.hpp"

namespace tcalc::ast {

FunctionNode::FunctionNode(std::string name)
  : FunctionNode{ std::move(name), {} }
{
}

FunctionNode::FunctionNode(std::string name,
                           std::vector<std::shared_ptr<Node>> args)
  : Node{ NodeType::FUNCTION }
  , _name{ std::move(name) }
  , _args{ std::move(args) }
{
}

}
