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
#include <string>
#include <unordered_map>

namespace tcalc::token {

/**
 * @brief Token type, some values are ASCII code of the corresponding character.
 *
 */
enum class TokenType : uint8_t
{
  PLUS,         /**< + operator. */
  MINUS,        /**< - operator. */
  MULTIPLY,     /**< * operator. */
  DIVIDE,       /**< / operator. */
  LPAREN,       /**< Bracket start. */
  RPAREN,       /**< Bracket end. */
  COMMA,        /**< Comma. */
  SEMICOLON,    /**< Semicolon. */
  ASSIGN,       /**< Assignment. */
  GREATER,      /**< > operator. */
  LESS,         /**< < operator. */
  NOT,          /**< ! operator. */
  NUMBER,       /**< Constant number. */
  IDENTIFIER,   /**< Variable or function name. */
  DEF,          /**< Function definition. */
  LET,          /**< Variable definition. */
  IF,           /**< If statement. */
  THEN,         /**< Then keyword. */
  ELSE,         /**< Else keyword. */
  IMPORT,       /**< Import statement. */
  EQUAL,        /**< == operator. */
  NOTEQUAL,     /**< != operator. */
  GREATEREQUAL, /**< >= operator. */
  LESSEQUAL,    /**< <= operator. */
  AND,          /**< && operator. */
  OR,           /**< || operator. */
  EOI,          /**< End of input. */
};

/**
 * @brief Token structure.
 *
 */
struct Token
{
  TokenType type;
  std::string text;
};

inline const std::unordered_map<TokenType, std::string> TOKEN_TYPE_NAMES = {
  { TokenType::PLUS, "PLUS" },
  { TokenType::MINUS, "MINUS" },
  { TokenType::MULTIPLY, "MULTIPLY" },
  { TokenType::DIVIDE, "DIVIDE" },
  { TokenType::LPAREN, "LPAREN" },
  { TokenType::RPAREN, "RPAREN" },
  { TokenType::COMMA, "COMMA" },
  { TokenType::SEMICOLON, "SEMICOLON" },
  { TokenType::ASSIGN, "ASSIGN" },
  { TokenType::GREATER, "GREATER" },
  { TokenType::LESS, "LESS" },
  { TokenType::NOT, "NOT" },
  { TokenType::NUMBER, "NUMBER" },
  { TokenType::IDENTIFIER, "IDENTIFIER" },
  { TokenType::DEF, "DEF" },
  { TokenType::LET, "LET" },
  { TokenType::IF, "IF" },
  { TokenType::THEN, "THEN" },
  { TokenType::ELSE, "ELSE" },
  { TokenType::IMPORT, "IMPORT" },
  { TokenType::EQUAL, "EQUAL" },
  { TokenType::NOTEQUAL, "NOTEQUAL" },
  { TokenType::GREATEREQUAL, "GREATEREQUAL" },
  { TokenType::LESSEQUAL, "LESSEQUAL" },
  { TokenType::AND, "AND" },
  { TokenType::OR, "OR" },
  { TokenType::EOI, "EOI" },
}; /**< Token type names. */

}
