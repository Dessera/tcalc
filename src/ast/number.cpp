#include "tcalc/ast/number.hpp"

namespace tcalc::ast {

NumberNode::NumberNode(double value)
  : Node{ NodeType::NUMBER }
  , _value{ value }
{
}

}
