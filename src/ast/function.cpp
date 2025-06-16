#include "tcalc/ast/function.hpp"

namespace tcalc::ast {

FcallNode::FcallNode(std::string name)
  : FcallNode{ std::move(name), {} }
{
}

FcallNode::FcallNode(std::string name, std::vector<std::shared_ptr<Node>> args)
  : Node{ NodeType::FCALL }
  , _name{ std::move(name) }
  , _args{ std::move(args) }
{
}

}
