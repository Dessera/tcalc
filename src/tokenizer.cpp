#include <cctype>

#include "magic_enum/magic_enum.hpp"
#include "tcalc/error.hpp"
#include "tcalc/token.hpp"
#include "tcalc/tokenizer.hpp"

namespace tcalc::token {

Tokenizer::Tokenizer(std::string_view input)
  : _input{ input }
  , _pos{ _input.begin() }
{
}

error::Result<Token>
Tokenizer::next()
{
  if (_pos >= _input.end()) {
    return Token{ .type = TokenType::EOI, .text = "" };
  }

  _skip_with(isspace);

  if (std::iscntrl(*_pos)) {
    return error::err(error::Code::SYNTAX_ERROR,
                      "Unexpected control character '{}', index: {}",
                      *_pos,
                      std::distance(_input.cbegin(), _pos));
  }

  if (auto res = magic_enum::enum_cast<TokenType>(*_pos); res.has_value()) {
    return Token{ .type = res.value(), .text = std::string{ *_pos++ } };
  }

  // TODO: real float parsing
  if (std::isdigit(*_pos)) {
    return _next_with(TokenType::NUMBER, isdigit);
  }

  if (std::isalpha(*_pos)) {
    return _next_with(TokenType::IDENTIFIER, isalnum);
  }

  return error::err(error::Code::SYNTAX_ERROR,
                    "Unexpected character '{}', index: {}",
                    *_pos,
                    std::distance(_input.cbegin(), _pos));
}

}
