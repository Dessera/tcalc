/**
 * @file control_flow.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Control flow nodes.
 * @version 0.1.0
 * @date 2025-06-17
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
 * @brief If node.
 *
 */
class TCALC_PUBLIC IfNode : public Node
{
private:
  NodePtr<> _cond;
  NodePtr<> _then;
  NodePtr<> _else;

public:
  /**
   * @brief Construct a new If Node object without nodes.
   *
   */
  IfNode();

  /**
   * @brief Construct a new If Node object with nodes.
   *
   * @param cond Condition node.
   * @param then Then node.
   * @param else_ Else node.
   */
  IfNode(NodePtr<> cond, NodePtr<> then, NodePtr<> else_);

  ~IfNode() override = default;

  /**
   * @brief Get the condition node.
   *
   * @return const NodePtr<>& Condition node.
   */
  [[nodiscard]] constexpr auto& cond() const noexcept { return _cond; }

  /**
   * @brief Get the condition node.
   *
   * @return NodePtr<>& Condition node.
   */
  [[nodiscard]] constexpr auto& cond() noexcept { return _cond; }

  /**
   * @brief Set the condition node.
   *
   * @param cond Condition node.
   */
  constexpr void cond(NodePtr<> cond) noexcept { _cond = std::move(cond); }

  /**
   * @brief Get the then node.
   *
   * @return const NodePtr<>& Then node.
   */
  [[nodiscard]] constexpr auto& then() const noexcept { return _then; }

  /**
   * @brief Get the then node.
   *
   * @return NodePtr<>& Then node.
   */
  [[nodiscard]] constexpr auto& then() noexcept { return _then; }

  /**
   * @brief Set the then node.
   *
   * @param then Then node.
   */
  constexpr void then(NodePtr<> then) noexcept { _then = std::move(then); }

  /**
   * @brief Get the else node.
   *
   * @return const NodePtr<>& Else node.
   */
  [[nodiscard]] constexpr auto& else_() const noexcept { return _else; }

  /**
   * @brief Get the else node.
   *
   * @return NodePtr<>& Else node.
   */
  [[nodiscard]] constexpr auto& else_() noexcept { return _else; }

  /**
   * @brief Set the else node.
   *
   * @param else_ Else node.
   */
  constexpr void else_(NodePtr<> else_) noexcept { _else = std::move(else_); }
};

}
