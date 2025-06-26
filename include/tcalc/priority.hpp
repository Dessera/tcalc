/**
 * @file priority.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Operator priority table.
 * @version 0.2.0
 * @date 2025-06-17
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <unordered_map>
#include <vector>

#include "tcalc/ast/node.hpp"
#include "tcalc/token.hpp"

namespace tcalc::ast {

/**
 * @brief Operator priority table type.
 *
 */
using PriorityTable =
  std::vector<std::unordered_map<token::TokenType, NodeType>>;

inline const PriorityTable BINOP_PRIORITY = {
  {
    { token::TokenType::AND, NodeType::BINARY_AND },
    { token::TokenType::OR, NodeType::BINARY_OR },
  },
  {
    { token::TokenType::EQUAL, NodeType::BINARY_EQUAL },
    { token::TokenType::NOTEQUAL, NodeType::BINARY_NOT_EQUAL },
    { token::TokenType::GREATER, NodeType::BINARY_GREATER },
    { token::TokenType::GREATEREQUAL, NodeType::BINARY_GREATER_EQUAL },
    { token::TokenType::LESS, NodeType::BINARY_LESS },
    { token::TokenType::LESSEQUAL, NodeType::BINARY_LESS_EQUAL },
  },
  {
    { token::TokenType::PLUS, NodeType::BINARY_PLUS },
    { token::TokenType::MINUS, NodeType::BINARY_MINUS },
  },
  {
    { token::TokenType::MULTIPLY, NodeType::BINARY_MULTIPLY },
    { token::TokenType::DIVIDE, NodeType::BINARY_DIVIDE },
  }
}; /**< Binary operator priority table. */

inline const PriorityTable UNARYOP_PRIORITY = { {
  { token::TokenType::PLUS, NodeType::UNARY_PLUS },
  { token::TokenType::MINUS, NodeType::UNARY_MINUS },
  { token::TokenType::NOT, NodeType::UNARY_NOT },
} }; /**< Unary operator priority table. */

}
