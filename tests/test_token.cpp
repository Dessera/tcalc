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
    { tcalc::token::TokenType::PLUS, "+" },
    { tcalc::token::TokenType::MINUS, "-" },
    { tcalc::token::TokenType::MULTIPLY, "*" },
    { tcalc::token::TokenType::DIVIDE, "/" },
    { tcalc::token::TokenType::LPAREN, "(" },
    { tcalc::token::TokenType::RPAREN, ")" },
    { tcalc::token::TokenType::COMMA, "," },
    { tcalc::token::TokenType::SEMICOLON, ";" },
    { tcalc::token::TokenType::ASSIGN, "=" },
    { tcalc::token::TokenType::GREATER, ">" },
    { tcalc::token::TokenType::LESS, "<" },
    { tcalc::token::TokenType::NOT, "!" },
    { tcalc::token::TokenType::NUMBER, "123.456" },
    { tcalc::token::TokenType::IDENTIFIER, "A10'.BC" },
    { tcalc::token::TokenType::DEF, "def" },
    { tcalc::token::TokenType::LET, "let" },
    { tcalc::token::TokenType::IF, "if" },
    { tcalc::token::TokenType::THEN, "then" },
    { tcalc::token::TokenType::ELSE, "else" },
    { tcalc::token::TokenType::IMPORT, "import" },
    { tcalc::token::TokenType::EQUAL, "==" },
    { tcalc::token::TokenType::NOTEQUAL, "!=" },
    { tcalc::token::TokenType::GREATEREQUAL, ">=" },
    { tcalc::token::TokenType::LESSEQUAL, "<=" },
    { tcalc::token::TokenType::AND, "&&" },
    { tcalc::token::TokenType::OR, "||" },
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
