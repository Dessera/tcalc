#include <cassert>
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <vector>

#include "tcalc/token.hpp"
#include "tcalc/tokenizer.hpp"

namespace {

std::vector<tcalc::token::Token>
tokenize(std::string_view input)
{
  using tcalc::token::Token;
  using tcalc::token::Tokenizer;
  using tcalc::token::TokenType;

  auto tokenizer = Tokenizer{ input };

  auto tokens = std::vector<Token>{};
  while (true) {
    auto res = tokenizer.next();
    REQUIRE(res.has_value());

    const auto& token = res.value();
    if (token.type == TokenType::EOI) {
      break;
    }

    tokens.push_back(token);
  }

  return tokens;
}

}

TEST_CASE("Test Tokenizer", "[tokenizer][success]")
{
  using tcalc::token::Token;
  using tcalc::token::TokenType;

  auto expected_tokens = std::vector<Token>{
    { .type = TokenType::NUMBER, .text = "1" },
    { .type = TokenType::PLUS, .text = "+" },
    { .type = TokenType::NUMBER, .text = "2" },
    { .type = TokenType::MULTIPLY, .text = "*" },
    { .type = TokenType::NUMBER, .text = "3" },
    { .type = TokenType::MINUS, .text = "-" },
    { .type = TokenType::IDENTIFIER, .text = "sqrt" },
    { .type = TokenType::LPAREN, .text = "(" },
    { .type = TokenType::NUMBER, .text = "9" },
    { .type = TokenType::RPAREN, .text = ")" },
    { .type = TokenType::DIVIDE, .text = "/" },
    { .type = TokenType::IDENTIFIER, .text = "pi" },
  };

  auto real_tokens = tokenize("1 + 2 * 3 - sqrt(9) / pi");

  REQUIRE(real_tokens.size() == expected_tokens.size());

  for (std::size_t i = 0; i < real_tokens.size(); ++i) {
    REQUIRE((real_tokens[i] == expected_tokens[i]));
  }
}

TEST_CASE("Test Tokenizer Error", "[tokenizer][error]")
{
  using tcalc::token::Tokenizer;

  // cntrl
  auto tk1 = Tokenizer{ "\b" };
  auto res = tk1.next();
  REQUIRE_FALSE(res.has_value());

  // printable
  auto tk2 = Tokenizer{ ";" };
  res = tk2.next();
  REQUIRE_FALSE(res.has_value());
}
