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

#include <cstdint>

#include "tcalc/common.hpp"

namespace tcalc::ast {

/**
 * @brief AST node type.
 *
 */
enum class NodeType : uint8_t
{
  BINARY_PLUS,     /**< Binary plus operator. */
  BINARY_MINUS,    /**< Binary minus operator. */
  BINARY_MULTIPLY, /**< Binary multiply operator. */
  BINARY_DIVIDE,   /**< Binary divide operator. */
  UNARY_PLUS,      /**< Unary plus operator. */
  UNARY_MINUS,     /**< Unary minus operator. */
  NUMBER,          /**< Constant number. */
  VARIABLE,        /**< Variable. */
  FUNCTION,        /**< Function call. */
};

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
  [[nodiscard]] constexpr auto type() const noexcept { return _type; }
};

}
