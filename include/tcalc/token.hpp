/**
 * @file token.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Input token definition.
 * @version 0.1.0
 * @date 2025-06-14
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cstdint>
#include <format>
#include <string_view>

#include "tcalc/common.hpp"

namespace tcalc::token {

/**
 * @brief Token type, some values are ASCII code of the corresponding character.
 *
 */
enum class TokenType : int8_t
{
  PLUS = 0x2b,        /**< + operator. */
  MINUS = 0x2d,       /**< - operator. */
  MULTIPLY = 0x2a,    /**< * operator. */
  DIVIDE = 0x2f,      /**< / operator. */
  LPAREN = 0x28,      /**< Bracket start. */
  RPAREN = 0x29,      /**< Bracket end. */
  COMMA = 0x2c,       /**< Comma. */
  ASSIGN = 0x3d,      /**< Assignment. */
  NUMBER = -0x01,     /**< Constant number. */
  IDENTIFIER = -0x02, /**< Variable or function name. */
  DEF = -0x03,        /**< Function definition. */
  LET = -0x04,        /**< Variable definition. */
  IF = -0x05,         /**< If statement. */
  THEN = -0x06,       /**< Then keyword. */
  ELSE = -0x07,       /**< Else keyword. */
  EOI = -0x08,        /**< End of input. */
};

/**
 * @brief Convert token type to readable string (wrapper of magic_enum).
 *
 * @param type Token type.
 * @return std::string Readable string.
 */
TCALC_PUBLIC std::string_view
token_type_to_string(TokenType type);

/**
 * @brief Token structure.
 *
 */
struct Token
{
  TokenType type;
  std::string text;
};

}

constexpr bool
operator==(const tcalc::token::Token& lhs, const tcalc::token::Token& rhs)
{
  return lhs.type == rhs.type && lhs.text == rhs.text;
}

constexpr bool
operator!=(const tcalc::token::Token& lhs, const tcalc::token::Token& rhs)
{
  return !(lhs == rhs);
}

template<typename CharT>
struct std::formatter<tcalc::token::Token, CharT>
{
  constexpr auto parse(auto& ctx) { return ctx.begin(); }

  constexpr auto format(const auto& token, auto& ctx) const
  {
    return std::format_to(ctx.out(),
                          "Token({}, {})",
                          tcalc::token::token_type_to_string(token.type),
                          token.text);
  }
};
