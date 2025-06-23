#include "tcalc/ast/node.hpp"

namespace tcalc::ast {

const std::unordered_map<NodeType, std::string> NODE_TYPE_NAMES = {
  { NodeType::BINARY_PLUS, "BINARY_PLUS" },
  { NodeType::BINARY_MINUS, "BINARY_MINUS" },
  { NodeType::BINARY_MULTIPLY, "BINARY_MULTIPLY" },
  { NodeType::BINARY_DIVIDE, "BINARY_DIVIDE" },
  { NodeType::BINARY_EQUAL, "BINARY_EQUAL" },
  { NodeType::BINARY_NOT_EQUAL, "BINARY_NOT_EQUAL" },
  { NodeType::BINARY_GREATER, "BINARY_GREATER" },
  { NodeType::BINARY_GREATER_EQUAL, "BINARY_GREATER_EQUAL" },
  { NodeType::BINARY_LESS, "BINARY_LESS" },
  { NodeType::BINARY_LESS_EQUAL, "BINARY_LESS_EQUAL" },
  { NodeType::BINARY_AND, "BINARY_AND" },
  { NodeType::BINARY_OR, "BINARY_OR" },
  { NodeType::UNARY_PLUS, "UNARY_PLUS" },
  { NodeType::UNARY_MINUS, "UNARY_MINUS" },
  { NodeType::UNARY_NOT, "UNARY_NOT" },
  { NodeType::NUMBER, "NUMBER" },
  { NodeType::VARREF, "VARREF" },
  { NodeType::VARASSIGN, "VARASSIGN" },
  { NodeType::FCALL, "FCALL" },
  { NodeType::FDEF, "FDEF" },
  { NodeType::IF, "IF" },
  { NodeType::PROGRAM, "PROGRAM" },
  { NodeType::IMPORT, "IMPORT" },
};

Node::Node(NodeType type)
  : _type{ type }
{
}

}
