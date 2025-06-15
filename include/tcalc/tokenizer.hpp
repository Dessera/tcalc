/**
 * @file tokenizer.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Tokenize the input string into tokens.
 * @version 0.1.0
 * @date 2025-06-14
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include "tcalc/common.hpp"
#include "tcalc/error.hpp"
#include "tcalc/token.hpp"

namespace tcalc::token {

/**
 * @brief Tokenize the input string into tokens.
 *
 */
class TCALC_PUBLIC Tokenizer
{
private:
  std::string _input;
  std::string::const_iterator _pos;

public:
  /**
   * @brief Construct a new Tokenizer object.
   *
   * @param input The input string.
   */
  explicit Tokenizer(std::string input);

  /**
   * @brief Get the next token.
   *
   * @return Token The next token.
   */
  error::Result<Token> next();

private:
  /**
   * @brief Get the next token with the given type and predicate.
   *
   * @param type The type of the token.
   * @param pred The predicate to check if the current character is valid.
   * @return Token The token.
   */
  constexpr auto _next_with(TokenType type, auto&& pred)
  {
    auto start = _pos;
    while (_pos != _input.end() && pred(*_pos)) {
      ++_pos;
    }
    return Token{ .type = type, .text = std::string{ start, _pos } };
  }

  /**
   * @brief Skip the characters with the given predicate.
   *
   * @param pred The predicate to check if the current character is valid.
   */
  constexpr void _skip_with(auto&& pred)
  {
    while (_pos != _input.end() && pred(*_pos)) {
      ++_pos;
    }
  }
};

}
