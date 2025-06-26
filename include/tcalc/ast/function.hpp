/**
 * @file function.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Function node.
 * @version 0.1.0
 * @date 2025-06-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <string>
#include <utility>
#include <vector>

#include "tcalc/ast/node.hpp"
#include "tcalc/common.hpp"

namespace tcalc::ast {

/**
 * @brief Function node.
 *
 */
class FcallNode : public Node
{
private:
  std::string _name;
  std::vector<NodePtr<>> _args;

public:
  /**
   * @brief Construct a new Function Node object.
   *
   * @param name Function name.
   */
  explicit FcallNode(std::string name)
    : FcallNode{ std::move(name), {} }
  {
  }

  /**
   * @brief Construct a new Function Node object.
   *
   * @param name Function name.
   * @param args Function arguments.
   */
  FcallNode(std::string name, std::vector<NodePtr<>> args)
    : Node{ NodeType::FCALL }
    , _name{ std::move(name) }
    , _args{ std::move(args) }
  {
  }

  ~FcallNode() override = default;

  /**
   * @brief Get function arguments.
   *
   * @return const std::vector<NodePtr<>>& Function arguments.
   */
  [[nodiscard]] TCALC_INLINE auto& args() const noexcept { return _args; }

  /**
   * @brief Get function arguments.
   *
   * @return std::vector<NodePtr<>>& Function arguments.
   */
  TCALC_INLINE auto& args() noexcept { return _args; }

  /**
   * @brief Push a function argument.
   *
   * @param arg Argument to push.
   */
  TCALC_INLINE void push_arg(const NodePtr<>& arg) { _args.push_back(arg); }

  /**
   * @brief Get function name.
   *
   * @return const std::string& Function name.
   */
  [[nodiscard]] TCALC_INLINE auto& name() const noexcept { return _name; }

  /**
   * @brief Set function name.
   *
   * @param name Function name.
   */
  TCALC_INLINE void name(std::string name) { _name = std::move(name); }
};

/**
 * @brief Function definition node.
 *
 */
class FdefNode : public Node
{
private:
  std::string _name;
  std::vector<std::string> _args;
  NodePtr<> _body;

public:
  /**
   * @brief Construct a new Fdef Node object only with name.
   *
   * @param name Function name.
   */
  explicit FdefNode(std::string name)
    : FdefNode{ std::move(name), {}, {} }
  {
  }

  /**
   * @brief Construct a new Fdef Node object with arguments and body.
   *
   * @param name Function name.
   * @param args Function arguments.
   * @param body Function body.
   */
  FdefNode(std::string name, std::vector<std::string> args, NodePtr<> body)
    : Node{ NodeType::FDEF }
    , _name{ std::move(name) }
    , _args{ std::move(args) }
    , _body{ std::move(body) }
  {
  }

  ~FdefNode() override = default;

  /**
   * @brief Get function arguments.
   *
   * @return const std::vector<std::string>& Function arguments.
   */
  [[nodiscard]] TCALC_INLINE auto& args() const noexcept { return _args; }

  /**
   * @brief Get function arguments.
   *
   * @return std::vector<std::string>& Function arguments.
   */
  TCALC_INLINE auto& args() noexcept { return _args; }

  /**
   * @brief Push a function argument.
   *
   * @param arg Argument to push.
   */
  TCALC_INLINE void push_arg(const std::string& arg) { _args.push_back(arg); }

  /**
   * @brief Get function body.
   *
   * @return const NodePtr<>& Function body.
   */
  [[nodiscard]] TCALC_INLINE auto& body() const noexcept { return _body; }

  /**
   * @brief Get function body.
   *
   * @return NodePtr<>& Function body.
   */
  TCALC_INLINE auto& body() noexcept { return _body; }

  /**
   * @brief Set function body.
   *
   * @param body Function body.
   */
  TCALC_INLINE void body(NodePtr<> body) { _body = std::move(body); }

  /**
   * @brief Get function name.
   *
   * @return const std::string& Function name.
   */
  [[nodiscard]] TCALC_INLINE auto& name() const noexcept { return _name; }

  /**
   * @brief Set function name.
   *
   * @param name Function name.
   */
  TCALC_INLINE void name(std::string name) { _name = std::move(name); }
};

}
