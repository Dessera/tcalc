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
class TCALC_PUBLIC VarRefNode : public Node
{
private:
  std::string _name;

public:
  /**
   * @brief Construct a new Variable Node object.
   *
   * @param name Variable name.
   */
  explicit VarRefNode(std::string name);

  ~VarRefNode() override = default;

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

/**
 * @brief Variable assign node.
 *
 */
class TCALC_PUBLIC VarAssignNode : public Node
{
private:
  std::string _name;
  NodePtr<> _body;

public:
  /**
   * @brief Construct a new Var Assign Node object.
   *
   * @param name Variable name.
   */
  VarAssignNode(std::string name);

  /**
   * @brief Construct a new Var Assign Node object with body.
   *
   * @param name Variable name.
   * @param body Variable body.
   */
  VarAssignNode(std::string name, NodePtr<> body);

  ~VarAssignNode() override = default;

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

  /**
   * @brief Get variable body.
   *
   * @return const NodePtr<>& Variable body.
   */
  [[nodiscard]] constexpr auto& body() const noexcept { return _body; }

  /**
   * @brief Get variable body.
   *
   * @return NodePtr<>& Variable body.
   */
  [[nodiscard]] constexpr auto& body() noexcept { return _body; }

  /**
   * @brief Set variable body.
   *
   * @param body Variable body.
   */
  constexpr void body(NodePtr<> body) noexcept { _body = std::move(body); }
};

}
