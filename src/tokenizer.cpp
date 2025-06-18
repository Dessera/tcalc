#include <cctype>
#include <magic_enum/magic_enum.hpp>

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
  _skip_with(_is_skippable_char);

  if (_pos >= _input.end()) {
    return Token{ .type = TokenType::EOI, .text = "" };
  }

  if (std::iscntrl(*_pos)) {
    return error::err(error::Code::SYNTAX_ERROR,
                      "Unexpected control character '{}', index: {}",
                      *_pos,
                      std::distance(_input.cbegin(), _pos));
  }

  for (const auto& [key, value] : KEYWORDS) {
    if (_is_keyword(key)) {
      _pos += key.size();
      return Token{ .type = value, .text = std::string{ key } };
    }
  }

  if (std::isdigit(*_pos)) {
    return _parse_number();
  }

  if (*_pos == QUOTE) {
    return _parse_quoted_identifier();
  }

  if (_is_first_identifier_char(*_pos)) {
    return _next_with(TokenType::IDENTIFIER, _is_identifier_char);
  }

  return error::err(error::Code::SYNTAX_ERROR,
                    "Unexpected character '{}', index: {}",
                    *_pos,
                    std::distance(_input.cbegin(), _pos));
}

error::Result<Token>
Tokenizer::_parse_number()
{
  // accept number with dot
  const auto* start = _pos;
  _skip_with(isdigit);
  if (_pos != _input.end() && *_pos == '.') {
    ++_pos;

    if (_pos != _input.end() && isdigit(*_pos)) {
      _skip_with(isdigit);
    } else {
      return error::err(error::Code::SYNTAX_ERROR,
                        "Unexpected character '{}', index: {}",
                        *_pos,
                        std::distance(_input.cbegin(), _pos));
    }
  }

  return Token{ .type = TokenType::NUMBER, .text = std::string{ start, _pos } };
}

error::Result<Token>
Tokenizer::_parse_quoted_identifier()
{
  auto text = std::string{};

  ++_pos;

  while (_pos < _input.end() && *_pos != QUOTE) {
    if (*_pos == '\\') {
      ++_pos;
      if (_pos == _input.end()) {
        return error::err(error::Code::SYNTAX_ERROR,
                          "Unexpected end of input, index: {}",
                          std::distance(_input.cbegin(), _pos));
      }
    }

    text += *_pos;
    ++_pos;
  }
  if (_pos == _input.end()) {
    return error::err(error::Code::SYNTAX_ERROR,
                      "Unexpected end of input, index: {}",
                      std::distance(_input.cbegin(), _pos));
  }

  ++_pos;

  return Token{ .type = TokenType::IDENTIFIER, .text = text };
}

bool
Tokenizer::_is_keyword(std::string_view keyword)
{
  if (_pos + keyword.size() > _input.end()) {
    return false;
  }

  if (std::string_view{ _pos, keyword.size() } == keyword) {
    return true;
  }

  return false;
}

bool
Tokenizer::_is_identifier_char(char c)
{
  return std::isalnum(c) || c == '_';
}

bool
Tokenizer::_is_first_identifier_char(char c)
{
  return std::isalpha(c) || c == '_';
}

bool
Tokenizer::_is_skippable_char(char c)
{
  return std::isspace(c) || c == '\n' || c == '\t';
}
}
