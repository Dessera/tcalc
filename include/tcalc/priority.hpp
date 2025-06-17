/**
 * @file priority.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Operator priority table.
 * @version 0.1.0
 * @date 2025-06-17
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <unordered_map>
#include <vector>

#include "tcalc/ast/node.hpp"
#include "tcalc/common.hpp"
#include "tcalc/token.hpp"

namespace tcalc::ast {

/**
 * @brief Operator priority table type.
 *
 */
using PriorityTable =
  std::vector<std::unordered_map<token::TokenType, NodeType>>;

/**
 * @brief Binary operator priority table.
 *
 */
extern TCALC_PUBLIC const PriorityTable BINOP_PRIORITY;

/**
 * @brief Unary operator priority table.
 *
 */
extern TCALC_PUBLIC const PriorityTable UNARYOP_PRIORITY;

}
