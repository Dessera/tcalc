#include <print>
#include <vector>

#include "tcalc/token.hpp"
#include "tcalc/tokenizer.hpp"

int
main()
{
  using tcalc::token::Token;
  using tcalc::token::Tokenizer;
  using tcalc::token::TokenType;

  Tokenizer tk{ "1 + 2 * 3 / (4 - 5) + sqrt(9) + pi + e + pow(2, 2)" };

  std::vector<Token> tokens{};

  while (true) {
    auto res = tk.next();
    if (!res.has_value()) {
      res.error().log();
    }
    tokens.push_back(res.value());
    if (tokens.back().type == TokenType::EOI) {
      break;
    }
  }

  for (const auto& token : tokens) {
    std::println("{}", token);
  }
}
