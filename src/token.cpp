#include "tcalc/token.hpp"

namespace tcalc::token {

const std::unordered_map<TokenType, std::string> TOKEN_TYPE_NAMES = {
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
};

}
