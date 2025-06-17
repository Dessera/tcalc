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

#include <memory>
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
class TCALC_PUBLIC FcallNode : public Node
{
private:
  std::string _name;
  std::vector<std::shared_ptr<Node>> _args;

public:
  /**
   * @brief Construct a new Function Node object.
   *
   * @param name Function name.
   */
  explicit FcallNode(std::string name);

  /**
   * @brief Construct a new Function Node object.
   *
   * @param name Function name.
   * @param args Function arguments.
   */
  FcallNode(std::string name, std::vector<std::shared_ptr<Node>> args);

  ~FcallNode() override = default;

  /**
   * @brief Get function arguments.
   *
   * @return const std::vector<std::shared_ptr<Node>>& Function arguments.
   */
  [[nodiscard]] constexpr auto& args() const noexcept { return _args; }

  /**
   * @brief Get function arguments.
   *
   * @return std::vector<std::shared_ptr<Node>>& Function arguments.
   */
  [[nodiscard]] constexpr auto& args() noexcept { return _args; }

  /**
   * @brief Push a function argument.
   *
   * @param arg Argument to push.
   */
  constexpr void push_arg(const std::shared_ptr<Node>& arg)
  {
    _args.push_back(arg);
  }

  /**
   * @brief Get function name.
   *
   * @return const std::string& Function name.
   */
  [[nodiscard]] constexpr auto& name() const noexcept { return _name; }

  /**
   * @brief Set function name.
   *
   * @param name Function name.
   */
  constexpr void name(std::string name) { _name = std::move(name); }
};

/**
 * @brief Function definition node.
 *
 */
class TCALC_PUBLIC FdefNode : public Node
{
private:
  std::string _name;
  std::vector<std::string> _args;
  std::shared_ptr<Node> _body;

public:
  /**
   * @brief Construct a new Fdef Node object only with name.
   *
   * @param name Function name.
   */
  explicit FdefNode(std::string name);

  /**
   * @brief Construct a new Fdef Node object with arguments and body.
   *
   * @param name Function name.
   * @param args Function arguments.
   * @param body Function body.
   */
  FdefNode(std::string name,
           std::vector<std::string> args,
           std::shared_ptr<Node> body);

  ~FdefNode() override = default;

  /**
   * @brief Get function arguments.
   *
   * @return const std::vector<std::string>& Function arguments.
   */
  [[nodiscard]] constexpr auto& args() const noexcept { return _args; }

  /**
   * @brief Get function arguments.
   *
   * @return std::vector<std::string>& Function arguments.
   */
  [[nodiscard]] constexpr auto& args() noexcept { return _args; }

  /**
   * @brief Push a function argument.
   *
   * @param arg Argument to push.
   */
  constexpr void push_arg(const std::string& arg) { _args.push_back(arg); }

  /**
   * @brief Get function body.
   *
   * @return const std::shared_ptr<Node>& Function body.
   */
  [[nodiscard]] constexpr auto& body() const noexcept { return _body; }

  /**
   * @brief Get function body.
   *
   * @return std::shared_ptr<Node>& Function body.
   */
  [[nodiscard]] constexpr auto& body() noexcept { return _body; }

  /**
   * @brief Set function body.
   *
   * @param body Function body.
   */
  constexpr void body(std::shared_ptr<Node> body) { _body = std::move(body); }

  /**
   * @brief Get function name.
   *
   * @return const std::string& Function name.
   */
  [[nodiscard]] constexpr auto& name() const noexcept { return _name; }

  /**
   * @brief Set function name.
   *
   * @param name Function name.
   */
  constexpr void name(std::string name) { _name = std::move(name); }
};

}
