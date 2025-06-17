
#include "tcalc/priority.hpp"
#include "tcalc/ast/node.hpp"
#include "tcalc/token.hpp"

namespace {

using tcalc::token::TokenType;

}

namespace tcalc::ast {

const PriorityTable BINOP_PRIORITY = {
  {
    { TokenType::EQUAL, NodeType::BINARY_EQUAL },
    { TokenType::NOTEQUAL, NodeType::BINARY_NOT_EQUAL },
    { TokenType::GREATER, NodeType::BINARY_GREATER },
    { TokenType::GREATEREQUAL, NodeType::BINARY_GREATER_EQUAL },
    { TokenType::LESS, NodeType::BINARY_LESS },
    { TokenType::LESSEQUAL, NodeType::BINARY_LESS_EQUAL },
  },
  {
    { TokenType::PLUS, NodeType::BINARY_PLUS },
    { TokenType::MINUS, NodeType::BINARY_MINUS },
  },
  {
    { TokenType::MULTIPLY, NodeType::BINARY_MULTIPLY },
    { TokenType::DIVIDE, NodeType::BINARY_DIVIDE },
  }
};

const PriorityTable UNARYOP_PRIORITY = { {
  { TokenType::PLUS, NodeType::UNARY_PLUS },
  { TokenType::MINUS, NodeType::UNARY_MINUS },
} };

}
