#include <gtest/gtest.h>
#include <tcalc/tokenizer.hpp>
#include <vector>

namespace {

TEST(TokenizerTest, Success)
{
  auto tokens = tcalc::token::Tokenizer{
    "+ - * / ( ) , ; = > < ! 123.456 'A10\\'.BC' def let if "
    "then else import == != >= <= && ||"
  };
  auto parsed_tokens = std::vector<tcalc::token::Token>{};
  while (true) {
    auto res = tokens.next();
    EXPECT_TRUE(res.has_value());

    if (res.value().type == tcalc::token::TokenType::EOI) {
      break;
    }

    parsed_tokens.push_back(res.value());
  }

  auto expected_tokens = std::vector<tcalc::token::Token>{
    { .type = tcalc::token::TokenType::PLUS, .text = "+" },
    { .type = tcalc::token::TokenType::MINUS, .text = "-" },
    { .type = tcalc::token::TokenType::MULTIPLY, .text = "*" },
    { .type = tcalc::token::TokenType::DIVIDE, .text = "/" },
    { .type = tcalc::token::TokenType::LPAREN, .text = "(" },
    { .type = tcalc::token::TokenType::RPAREN, .text = ")" },
    { .type = tcalc::token::TokenType::COMMA, .text = "," },
    { .type = tcalc::token::TokenType::SEMICOLON, .text = ";" },
    { .type = tcalc::token::TokenType::ASSIGN, .text = "=" },
    { .type = tcalc::token::TokenType::GREATER, .text = ">" },
    { .type = tcalc::token::TokenType::LESS, .text = "<" },
    { .type = tcalc::token::TokenType::NOT, .text = "!" },
    { .type = tcalc::token::TokenType::NUMBER, .text = "123.456" },
    { .type = tcalc::token::TokenType::IDENTIFIER, .text = "A10'.BC" },
    { .type = tcalc::token::TokenType::DEF, .text = "def" },
    { .type = tcalc::token::TokenType::LET, .text = "let" },
    { .type = tcalc::token::TokenType::IF, .text = "if" },
    { .type = tcalc::token::TokenType::THEN, .text = "then" },
    { .type = tcalc::token::TokenType::ELSE, .text = "else" },
    { .type = tcalc::token::TokenType::IMPORT, .text = "import" },
    { .type = tcalc::token::TokenType::EQUAL, .text = "==" },
    { .type = tcalc::token::TokenType::NOTEQUAL, .text = "!=" },
    { .type = tcalc::token::TokenType::GREATEREQUAL, .text = ">=" },
    { .type = tcalc::token::TokenType::LESSEQUAL, .text = "<=" },
    { .type = tcalc::token::TokenType::AND, .text = "&&" },
    { .type = tcalc::token::TokenType::OR, .text = "||" },
  };

  EXPECT_EQ(parsed_tokens.size(), expected_tokens.size());
  for (size_t i = 0; i < parsed_tokens.size(); ++i) {
    EXPECT_EQ(parsed_tokens[i].text, expected_tokens[i].text);
    EXPECT_EQ(parsed_tokens[i].type, expected_tokens[i].type);
  }
}

TEST(TokenizerTest, Failure)
{
  auto tokens = tcalc::token::Tokenizer{ "." };
  auto res = tokens.next();
  EXPECT_FALSE(res.has_value());

  auto tokens2 = tcalc::token::Tokenizer{ "\b" };
  auto res2 = tokens2.next();
  EXPECT_FALSE(res2.has_value());
}

}
