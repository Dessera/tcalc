/**
 * @file variable.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Variable node.
 * @version 0.2.0
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
class VarRefNode : public Node
{
private:
  std::string _name;

public:
  /**
   * @brief Construct a new Variable Node object.
   *
   * @param name Variable name.
   */
  explicit VarRefNode(std::string name)
    : Node{ NodeType::VARREF }
    , _name{ std::move(name) }
  {
  }

  ~VarRefNode() override = default;

  /**
   * @brief Get variable name.
   *
   * @return const std::string& Variable name.
   */
  [[nodiscard]] TCALC_INLINE auto& name() const noexcept { return _name; }

  /**
   * @brief Set variable name.
   *
   * @param name Variable name.
   */
  TCALC_INLINE void name(std::string name) noexcept { _name = std::move(name); }
};

/**
 * @brief Variable assign node.
 *
 */
class VarAssignNode : public Node
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
  explicit VarAssignNode(std::string name)
    : VarAssignNode{ std::move(name), nullptr }
  {
  }

  /**
   * @brief Construct a new Var Assign Node object with body.
   *
   * @param name Variable name.
   * @param body Variable body.
   */
  VarAssignNode(std::string name, NodePtr<> body)
    : Node{ NodeType::VARASSIGN }
    , _name{ std::move(name) }
    , _body{ std::move(body) }
  {
  }

  ~VarAssignNode() override = default;

  /**
   * @brief Get variable name.
   *
   * @return const std::string& Variable name.
   */
  [[nodiscard]] TCALC_INLINE auto& name() const noexcept { return _name; }

  /**
   * @brief Set variable name.
   *
   * @param name Variable name.
   */
  TCALC_INLINE void name(std::string name) noexcept { _name = std::move(name); }

  /**
   * @brief Get variable body.
   *
   * @return const NodePtr<>& Variable body.
   */
  [[nodiscard]] TCALC_INLINE auto& body() const noexcept { return _body; }

  /**
   * @brief Get variable body.
   *
   * @return NodePtr<>& Variable body.
   */
  TCALC_INLINE auto& body() noexcept { return _body; }

  /**
   * @brief Set variable body.
   *
   * @param body Variable body.
   */
  TCALC_INLINE void body(NodePtr<> body) noexcept { _body = std::move(body); }
};

}
