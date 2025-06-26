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

#include <cstddef>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

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
public:
  constexpr static std::size_t MAX_CALL_DEPTH = 1000;

private:
  std::unordered_map<std::string, double> _vars;
  std::unordered_map<std::string, builtins::Function> _funcs;

  std::size_t _call_depth{ 0 };

public:
  /**
   * @brief Construct a new Eval Context object.
   *
   * @param vars Variables map.
   * @param funcs Built-in functions map.
   */
  EvalContext(std::unordered_map<std::string, double> vars,
              std::unordered_map<std::string, builtins::Function> funcs,
              std::size_t call_depth = 0)
    : _vars{ std::move(vars) }
    , _funcs{ std::move(funcs) }
    , _call_depth{ call_depth }
  {
  }

  EvalContext() = default;
  ~EvalContext() = default;

  /**
   * @brief Get variables.
   *
   * @return std::unordered_map<std::string, double>& Variables map.
   */
  [[nodiscard]] TCALC_INLINE auto& vars() noexcept { return _vars; }

  /**
   * @brief Get built-in functions.
   *
   * @return std::unordered_map<std::string, BuiltinFunc>& Built-in functions
   * map.
   */
  [[nodiscard]] TCALC_INLINE auto& funcs() noexcept { return _funcs; }

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
  TCALC_INLINE void var(const std::string& name, double value) noexcept
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
  TCALC_INLINE void func(const std::string& name,
                         builtins::Function func) noexcept
  {
    _funcs[name] = std::move(func);
  }

  /**
   * @brief Get the call depth.
   *
   * @return std::size_t Call depth.
   */
  [[nodiscard]] TCALC_INLINE auto call_depth() const noexcept
  {
    return _call_depth;
  }

  /**
   * @brief Set the call depth.
   *
   * @param depth Call depth.
   */
  TCALC_INLINE void call_depth(std::size_t depth) { _call_depth = depth; }

  /**
   * @brief Increment the call depth.
   *
   */
  TCALC_INLINE void increment_call_depth() noexcept { ++_call_depth; }

  /**
   * @brief Update the context with another context.
   *
   * @param ctx Other context.
   */
  void update_with(const EvalContext& ctx);
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
  explicit Evaluator(const EvalContext& ctx);

  /**
   * @brief Construct a default Evaluator object with default context.
   *
   */
  Evaluator()
    : Evaluator{ EvalContext{ builtins::BUILTIN_VARIABLES,
                              builtins::BUILTIN_FUNCTIONS } }
  {
  }

  ~Evaluator() = default;

  /**
   * @brief Get the evaluation context.
   *
   * @return const EvalContext& Evaluation context.
   */
  [[nodiscard]] TCALC_INLINE auto& ctx() const noexcept { return _ctx; }

  /**
   * @brief Evaluate an expression.
   *
   * @param input Expression string.
   * @return error::Result<double> Evaluation result.
   */
  error::Result<double> eval(std::string_view input);

  /**
   * @brief Evaluate a program.
   *
   * @param input Program string.
   * @return error::Result<std::vector<double>> Evaluation result.
   */
  error::Result<std::vector<double>> eval_prog(std::string_view input);
};

}
