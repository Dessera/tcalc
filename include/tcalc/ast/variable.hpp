/**
 * @file variable.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Variable node.
 * @version 0.1.0
 * @date 2025-06-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <string>
#include <utility>

#include "tcalc/ast/node.hpp"
#include "tcalc/common.hpp"

namespace tcalc::ast {

/**
 * @brief Variable node.
 *
 */
class TCALC_PUBLIC VariableNode : public Node
{
private:
  std::string _name;

public:
  /**
   * @brief Construct a new Variable Node object.
   *
   * @param name Variable name.
   */
  explicit VariableNode(std::string name);

  ~VariableNode() override = default;

  /**
   * @brief Get variable name.
   *
   * @return const std::string& Variable name.
   */
  [[nodiscard]] constexpr auto& name() const noexcept { return _name; }

  /**
   * @brief Set variable name.
   *
   * @param name Variable name.
   */
  constexpr void name(std::string name) noexcept { _name = std::move(name); }
};

}
