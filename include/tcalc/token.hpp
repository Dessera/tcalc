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
  LPAREN = 0x28,      /**< bracket start. */
  RPAREN = 0x29,      /**< bracket end. */
  COMMA = 0x2c,       /**< comma. */
  NUMBER = -0x01,     /**< constant number. */
  IDENTIFIER = -0x02, /**< variable or function name. */
  EOI = -0x03,        /**< end of input. */
  INVALID = -0x04,    /**< invalid token placeholder. */
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
