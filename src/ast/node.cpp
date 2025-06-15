#include "tcalc/ast/node.hpp"

namespace tcalc::ast {

Node::Node(NodeType type)
  : _type{ type }
{
}

}
