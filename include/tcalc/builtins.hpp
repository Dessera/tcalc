/**
 * @file builtins.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Built-in functions and variables.
 * @version 0.2.0
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cmath> // IWYU pragma: keep
#include <functional>
#include <unordered_map>
#include <vector>

#include "tcalc/ast/function.hpp"
#include "tcalc/ast/node.hpp"
#include "tcalc/ast/program.hpp"
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
  ast::NodePtr<ast::FdefNode> _node;

public:
  /**
   * @brief Construct a new Function Wrapper object.
   *
   * @param node Function definition node.
   */
  explicit FunctionWrapper(ast::NodePtr<ast::FdefNode> node)
    : _node{ std::move(node) }
  {
  }

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
 * @brief Wrapper for ProgramImportNode.
 *
 */
class TCALC_PUBLIC ImportWrapper
{
private:
  ast::NodePtr<ast::ProgramImportNode> _node;

public:
  /**
   * @brief Construct a new Import Wrapper object.
   *
   * @param node ProgramImportNode.
   */
  explicit ImportWrapper(ast::NodePtr<ast::ProgramImportNode> node)
    : _node{ std::move(node) }
  {
  }

  ~ImportWrapper() = default;

  /**
   * @brief Import the program.
   *
   * @param ctx Evaluation context.
   * @return error::Result<void> Result.
   */
  error::Result<void> import(EvalContext& ctx) const;
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

/**
 * @brief Built-in log function.
 *
 * @param args Function arguments.
 * @param ctx Evaluation context.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
log(const std::vector<double>& args, const EvalContext& ctx);

/**
 * @brief Built-in sin function.
 *
 * @param args Function arguments.
 * @param ctx Evaluation context.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
sin(const std::vector<double>& args, const EvalContext& ctx);

/**
 * @brief Built-in cos function.
 *
 * @param args Function arguments.
 * @param ctx Evaluation context.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
cos(const std::vector<double>& args, const EvalContext& ctx);

/**
 * @brief Built-in tan function.
 *
 * @param args Function arguments.
 * @param ctx Evaluation context.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
tan(const std::vector<double>& args, const EvalContext& ctx);

/**
 * @brief Built-in acos function.
 *
 * @param args Function arguments.
 * @param ctx Evaluation context.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
acos(const std::vector<double>& args, const EvalContext& ctx);

/**
 * @brief Built-in asin function.
 *
 * @param args Function arguments.
 * @param ctx Evaluation context.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
asin(const std::vector<double>& args, const EvalContext& ctx);

/**
 * @brief Built-in atan function.
 *
 * @param args Function arguments.
 * @param ctx Evaluation context.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
atan(const std::vector<double>& args, const EvalContext& ctx);

/**
 * @brief Built-in exp function.
 *
 * @param args Function arguments.
 * @param ctx Evaluation context.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
exp(const std::vector<double>& args, const EvalContext& ctx);

inline const std::unordered_map<std::string, double> BUILTIN_VARIABLES = {
  { "pi", M_PI },
  { "e", M_E },
}; /**< Built-in variables. */

inline const std::unordered_map<std::string, Function> BUILTIN_FUNCTIONS = {
  { "sqrt", sqrt }, { "pow", pow }, { "log", log },   { "sin", sin },
  { "cos", cos },   { "tan", tan }, { "acos", acos }, { "asin", asin },
  { "atan", atan }, { "exp", exp }
}; /**< Built-in functions. */

}
