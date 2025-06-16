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
#include <unordered_map>
#include <vector>

#include "tcalc/common.hpp"
#include "tcalc/error.hpp"

namespace tcalc::builtins {

/**
 * @brief Built-in function type.
 *
 */
using Function =
  std::function<error::Result<double>(const std::vector<double>&)>;

/**
 * @brief Built-in sqrt function.
 *
 * @param args Function arguments.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
sqrt(const std::vector<double>& args);

/**
 * @brief Built-in pow function.
 *
 * @param args Function arguments.
 * @return error::Result<double> Result.
 */
TCALC_PUBLIC error::Result<double>
pow(const std::vector<double>& args);

extern TCALC_PUBLIC const std::unordered_map<std::string, double>
  BUILTIN_VARIABLES; /**< Built-in variables. */

extern TCALC_PUBLIC const std::unordered_map<std::string, Function>
  BUILTIN_FUNCTIONS; /**< Built-in functions. */

}
