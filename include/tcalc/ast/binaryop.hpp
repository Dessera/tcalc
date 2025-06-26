/**
 * @file binaryop.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Binary operation node.
 * @version 0.1.0
 * @date 2025-06-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <utility>

#include "tcalc/ast/node.hpp"
#include "tcalc/common.hpp"

namespace tcalc::ast {

/**
 * @brief Binary operation base class.
 *
 */
class BinaryOpNode : public Node
{
private:
  NodePtr<> _left;
  NodePtr<> _right;

public:
  /**
   * @brief Construct a new Binary Op Node object with no subnodes.
   *
   * @param type Node type.
   */
  explicit BinaryOpNode(NodeType type)
    : BinaryOpNode{ type, nullptr, nullptr }
  {
  }

  /**
   * @brief Construct a new Binary Op Node object with subnodes.
   *
   * @param type Node type.
   * @param left Left subnode.
   * @param right Right subnode.
   */
  BinaryOpNode(NodeType type, NodePtr<> left, NodePtr<> right)
    : Node{ type }
    , _left{ std::move(left) }
    , _right{ std::move(right) }
  {
  }

  ~BinaryOpNode() override = default;

  /**
   * @brief Get the left subnode.
   *
   * @return const NodePtr<> Left subnode.
   */
  [[nodiscard]] TCALC_INLINE auto& left() const noexcept { return _left; }

  /**
   * @brief Get the left subnode.
   *
   * @return NodePtr<> Left subnode.
   */
  TCALC_INLINE auto& left() noexcept { return _left; }

  /**
   * @brief Set the left subnode.
   *
   * @param left Left subnode.
   */
  TCALC_INLINE void left(NodePtr<> left) noexcept { _left = std::move(left); }

  /**
   * @brief Get the right subnode.
   *
   * @return const NodePtr<> Right subnode.
   */
  [[nodiscard]] TCALC_INLINE auto& right() const noexcept { return _right; }

  /**
   * @brief Get the right subnode.
   *
   * @return NodePtr<> Right subnode.
   */
  TCALC_INLINE auto& right() noexcept { return _right; }

  /**
   * @brief Set the right subnode.
   *
   * @param right Right subnode.
   */
  TCALC_INLINE void right(NodePtr<> right) noexcept
  {
    _right = std::move(right);
  }
};

}
