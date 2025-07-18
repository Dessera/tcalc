/**
 * @file tokenizer.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Tokenize the input string into tokens.
 * @version 0.2.0
 * @date 2025-06-14
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <functional>
#include <map>
#include <string>
#include <string_view>

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
public:
  using KeywordComp =
    std::greater<std::string_view>; /**< Comparator for keywords. */

  inline static const std::map<std::string_view, TokenType, KeywordComp>
    KEYWORDS = {
      { "def", TokenType::DEF },         { "let", TokenType::LET },
      { "if", TokenType::IF },           { "then", TokenType::THEN },
      { "else", TokenType::ELSE },       { "import", TokenType::IMPORT },
      { "==", TokenType::EQUAL },        { "!=", TokenType::NOTEQUAL },
      { ">=", TokenType::GREATEREQUAL }, { "<=", TokenType::LESSEQUAL },
      { "&&", TokenType::AND },          { "||", TokenType::OR },
      { "+", TokenType::PLUS },          { "-", TokenType::MINUS },
      { "*", TokenType::MULTIPLY },      { "/", TokenType::DIVIDE },
      { "(", TokenType::LPAREN },        { ")", TokenType::RPAREN },
      { ",", TokenType::COMMA },         { ";", TokenType::SEMICOLON },
      { "=", TokenType::ASSIGN },        { ">", TokenType::GREATER },
      { "<", TokenType::LESS },          { "!", TokenType::NOT },
    }; /**< Tcalc keywords, must be ordered by length. */

  constexpr static char QUOTE = '\''; /**< The quote character. */

private:
  std::string_view _input;
  std::string_view::const_iterator _pos;

public:
  /**
   * @brief Construct a new Tokenizer object.
   *
   * @param input The input string.
   */
  explicit Tokenizer(std::string_view input)
    : _input{ input }
    , _pos{ _input.begin() }
  {
  }

  /**
   * @brief Get the next token.
   *
   * @return Token The next token.
   */
  error::Result<Token> next();

  /**
   * @brief Get the current position of the tokenizer.
   *
   * @return std::string_view::const_iterator The current position.
   */
  [[nodiscard]] TCALC_INLINE auto pos() const noexcept { return _pos; }

  /**
   * @brief Get the current position of the tokenizer as an index.
   *
   * @return size_t The current position as an index.
   */
  [[nodiscard]] TCALC_INLINE auto spos() const noexcept
  {
    return std::distance(_input.begin(), _pos);
  }

private:
  /**
   * @brief Get the next token with the given type and predicate.
   *
   * @param type The type of the token.
   * @param pred The predicate to check if the current character is valid.
   * @return Token The token.
   */
  template<typename Pred>
  auto _next_with(TokenType type, const Pred& pred)
  {
    const auto* start = _pos;
    while (_pos != _input.end() && pred(*_pos)) {
      ++_pos;
    }
    return Token{ type, std::string{ start, _pos } };
  }

  /**
   * @brief Skip the characters with the given predicate.
   *
   * @param pred The predicate to check if the current character is valid.
   */
  template<typename Pred>
  void _skip_with(const Pred& pred)
  {
    while (_pos != _input.end() && pred(*_pos)) {
      ++_pos;
    }
  }

  /**
   * @brief Parse the next number.
   *
   */
  error::Result<Token> _parse_number();

  /**
   * @brief Parse the next quoted identifier.
   *
   * @return error::Result<Token> The parsed token.
   */
  error::Result<Token> _parse_quoted_identifier();

  /**
   * @brief Check if the string is a keyword.
   *
   * @param keyword The keyword to check.
   * @return true If the string is a keyword.
   * @return false If the string is not a keyword.
   */
  bool _is_keyword(std::string_view keyword);

  /**
   * @brief Check if the character is a valid variable character.
   *
   * @param c The character to check.
   * @return true If the character is a valid variable character.
   * @return false If the character is not a valid variable character.
   */
  static bool _is_identifier_char(char c);

  /**
   * @brief Check if the character is a valid first variable character.
   *
   * @param c The character to check.
   * @return true If the character is a valid first variable character.
   * @return false If the character is not a valid first variable character.
   */
  static bool _is_first_identifier_char(char c);

  /**
   * @brief Check if the character is a valid skippable character.
   *
   * @param c The character to check.
   * @return true If the character is a valid skippable character.
   * @return false If the character is not a valid skippable character.
   */
  static bool _is_skippable_char(char c);
};

}
