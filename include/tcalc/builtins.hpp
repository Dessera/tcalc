/**
 * @file builtins.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Built-in functions and variables.
 * @version 0.1.0
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "tcalc/ast/function.hpp"
#include "tcalc/common.hpp"
#include "tcalc/error.hpp"

namespace tcalc {

class EvalContext;

}

namespace tcalc::builtins {

/**
 * @brief Built-in function type.
 *
 */
using Function = std::function<error::Result<double>(const std::vector<double>&,
                                                     const EvalContext&)>;

/**
 * @brief Wrapper for User-defined functions.
 *
 */
class TCALC_PUBLIC FunctionWrapper
{
private:
  std::shared_ptr<ast::FdefNode> _node;

public:
  /**
   * @brief Construct a new Function Wrapper object.
   *
   * @param node Function definition node.
   */
  FunctionWrapper(std::shared_ptr<ast::FdefNode> node);

  ~FunctionWrapper() = default;

  /**
   * @brief Evaluate the function.
   *
   * @param args Function arguments.
   * @param ctx Evaluation context.
   * @return error::Result<double> Evaluation result.
   */
  error::Result<double> operator()(const std::vector<double>& args,
                                   const EvalContext& ctx) const;
};

/**
 * @brief Built-in sqrt function.
 *
 * @param args Function arguments.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
sqrt(const std::vector<double>& args, const EvalContext& ctx);

/**
 * @brief Built-in pow function.
 *
 * @param args Function arguments.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
pow(const std::vector<double>& args, const EvalContext& ctx);

extern TCALC_PUBLIC const std::unordered_map<std::string, double>
  BUILTIN_VARIABLES; /**< Built-in variables. */

extern TCALC_PUBLIC const std::unordered_map<std::string, Function>
  BUILTIN_FUNCTIONS; /**< Built-in functions. */

}
