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

FdefNode::FdefNode(std::string name)
  : FdefNode{ std::move(name), {}, nullptr }
{
}

FdefNode::FdefNode(std::string name,
                   std::vector<std::string> args,
                   std::shared_ptr<Node> body)
  : Node{ NodeType::FDEF }
  , _name{ std::move(name) }
  , _args{ std::move(args) }
  , _body{ std::move(body) }
{
}

}
