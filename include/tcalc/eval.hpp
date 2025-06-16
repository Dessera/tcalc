/**
 * @file eval.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Evaluator for tcalc.
 * @version 0.1.0
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <string>
#include <unordered_map>
#include <utility>

#include "tcalc/builtins.hpp"
#include "tcalc/common.hpp"
#include "tcalc/error.hpp"
#include "tcalc/parser.hpp"

namespace tcalc {

/**
 * @brief Evaluation context which stores variables and built-in functions.
 *
 */
class TCALC_PUBLIC EvalContext
{
private:
  std::unordered_map<std::string, double> _vars;
  std::unordered_map<std::string, builtins::Function> _funcs;

public:
  /**
   * @brief Construct a new Eval Context object.
   *
   * @param vars Variables map.
   * @param funcs Built-in functions map.
   */
  EvalContext(std::unordered_map<std::string, double> vars,
              std::unordered_map<std::string, builtins::Function> funcs);

  EvalContext() = default;
  ~EvalContext() = default;

  /**
   * @brief Get variables.
   *
   * @return std::unordered_map<std::string, double>& Variables map.
   */
  constexpr auto& vars() { return _vars; }

  /**
   * @brief Get built-in functions.
   *
   * @return std::unordered_map<std::string, BuiltinFunc>& Built-in functions
   * map.
   */
  constexpr auto& funcs() { return _funcs; }

  /**
   * @brief Get a variable.
   *
   * @param name Variable name.
   * @return error::Result<double> Variable value result.
   */
  error::Result<double> var(const std::string& name) const;

  /**
   * @brief Set a variable.
   *
   * @param name Variable name.
   * @param value Variable value.
   */
  constexpr void var(const std::string& name, double value)
  {
    _vars[name] = value;
  }

  /**
   * @brief Get a built-in function.
   *
   * @param name Function name.
   * @return error::Result<BuiltinFunc> Function pointer result.
   */
  error::Result<builtins::Function> func(const std::string& name) const;

  /**
   * @brief Set a built-in function.
   *
   * @param name Function name.
   * @param func Function pointer.
   */
  constexpr void func(const std::string& name, builtins::Function func)
  {
    _funcs[name] = std::move(func);
  }
};

/**
 * @brief Evaluator for tcalc.
 *
 */
class TCALC_PUBLIC Evaluator
{
private:
  EvalContext _ctx;
  ast::Parser _parser{};

public:
  /**
   * @brief Construct a new Evaluator object.
   *
   * @param ctx Evaluation context.
   */
  Evaluator(const EvalContext& ctx);

  /**
   * @brief Construct a default Evaluator object with default context.
   *
   */
  Evaluator();

  ~Evaluator() = default;

  /**
   * @brief Evaluate an expression.
   *
   * @param input Expression string.
   * @return error::Result<double> Evaluation result.
   */
  error::Result<double> eval(std::string_view input);
};

}
