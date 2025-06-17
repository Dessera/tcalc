/**
 * @file unaryop.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Unary operation node.
 * @version 0.1.0
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <memory>
#include <utility>

#include "tcalc/ast/node.hpp"

namespace tcalc::ast {

/**
 * @brief Unary operation node.
 *
 */
class UnaryOpNode : public Node
{
private:
  std::shared_ptr<Node> _operand;

public:
  /**
   * @brief Construct a new Unary Op Node object without operand.
   *
   * @param type Node type.
   */
  UnaryOpNode(NodeType type);

  /**
   * @brief Construct a new Unary Op Node object with operand.
   *
   * @param type Node type.
   * @param operand Operand node.
   */
  UnaryOpNode(NodeType type, std::shared_ptr<Node> operand);

  ~UnaryOpNode() override = default;

  /**
   * @brief Get operand.
   *
   * @return const std::shared_ptr<Node>& Operand node.
   */
  [[nodiscard]] constexpr auto& operand() const noexcept { return _operand; }

  /**
   * @brief Get operand.
   *
   * @return std::shared_ptr<Node>& Operand node.
   */
  [[nodiscard]] constexpr auto& operand() noexcept { return _operand; }

  /**
   * @brief Set operand.
   *
   * @param operand Operand node.
   */
  constexpr void operand(std::shared_ptr<Node> operand) noexcept
  {
    _operand = std::move(operand);
  }
};

}
