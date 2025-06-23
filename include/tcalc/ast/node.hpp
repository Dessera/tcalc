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

extern const std::unordered_map<NodeType, std::string>
  NODE_TYPE_NAMES; /**< Node type names. */

/**
 * @brief Base class for AST nodes.
 *
 */
class TCALC_PUBLIC Node
{
private:
  NodeType _type;

public:
  /**
   * @brief Construct a new Node object.
   *
   * @param type Node type.
   */
  explicit Node(NodeType type);

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
