/**
 * @file number.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Number AST node.
 * @version 0.1.0
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include "tcalc/ast/node.hpp"
#include "tcalc/common.hpp"

namespace tcalc::ast {

/**
 * @brief Number AST node.
 *
 */
class NumberNode : public Node
{
private:
  double _value;

public:
  /**
   * @brief Construct a new Number Node object.
   *
   * @param value Number value.
   */
  explicit NumberNode(double value)
    : Node{ NodeType::NUMBER }
    , _value{ value }
  {
  }

  ~NumberNode() override = default;

  /**
   * @brief Get the number value.
   *
   * @return double Number value.
   */
  [[nodiscard]] TCALC_INLINE auto value() const noexcept { return _value; }

  /**
   * @brief Set the number value.
   *
   * @param value Number value.
   */
  TCALC_INLINE void value(double value) noexcept { _value = value; }
};

}
