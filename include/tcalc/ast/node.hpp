/**
 * @file node.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Base class for AST nodes.
 * @version 0.1.0
 * @date 2025-06-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cctype>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

#include "tcalc/common.hpp"

namespace tcalc::ast {

/**
 * @brief AST node type.
 *
 */
enum class NodeType : uint8_t
{
  BINARY_PLUS,          /**< Binary plus operator. */
  BINARY_MINUS,         /**< Binary minus operator. */
  BINARY_MULTIPLY,      /**< Binary multiply operator. */
  BINARY_DIVIDE,        /**< Binary divide operator. */
  BINARY_EQUAL,         /**< Binary equal operator. */
  BINARY_NOT_EQUAL,     /**< Binary not equal operator. */
  BINARY_GREATER,       /**< Binary greater operator. */
  BINARY_GREATER_EQUAL, /**< Binary greater equal operator. */
  BINARY_LESS,          /**< Binary less operator. */
  BINARY_LESS_EQUAL,    /**< Binary less equal operator. */
  BINARY_AND,           /**< Binary and operator. */
  BINARY_OR,            /**< Binary or operator. */
  UNARY_PLUS,           /**< Unary plus operator. */
  UNARY_MINUS,          /**< Unary minus operator. */
  UNARY_NOT,            /**< Unary not operator. */
  NUMBER,               /**< Constant number. */
  VARREF,               /**< Variable reference. */
  VARASSIGN,            /**< Variable assignment. */
  FCALL,                /**< Function call. */
  FDEF,                 /**< Function definition. */
  IF,                   /**< If statement. */
  PROGRAM,              /**< Program. */
  IMPORT,               /**< Import statement. */
};

inline const std::unordered_map<NodeType, std::string> NODE_TYPE_NAMES = {
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
}; /**< Node type names. */

/**
 * @brief Base class for AST nodes.
 *
 */
class Node
{
private:
  NodeType _type;

public:
  /**
   * @brief Construct a new Node object.
   *
   * @param type Node type.
   */
  explicit Node(NodeType type)
    : _type{ type }
  {
  }

  virtual ~Node() = default;

  /**
   * @brief Get the node type.
   *
   * @return NodeType Node type.
   */
  [[nodiscard]] TCALC_INLINE auto type() const noexcept { return _type; }
};

/**
 * @brief Shared pointer to a node.
 *
 * @tparam NT Node type.
 */
template<typename NT = Node>
  requires std::derived_from<NT, Node>
using NodePtr = std::shared_ptr<NT>;

}
