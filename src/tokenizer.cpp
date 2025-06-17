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

  // TODO: loop to handle these cases
  if (_is_keyword("def")) {
    _pos += 3;
    return Token{ .type = TokenType::DEF, .text = "def" };
  }

  if (_is_keyword("let")) {
    _pos += 3;
    return Token{ .type = TokenType::LET, .text = "let" };
  }

  if (_is_keyword("if")) {
    _pos += 2;
    return Token{ .type = TokenType::IF, .text = "if" };
  }

  if (_is_keyword("then")) {
    _pos += 4;
    return Token{ .type = TokenType::THEN, .text = "then" };
  }

  if (_is_keyword("else")) {
    _pos += 4;
    return Token{ .type = TokenType::ELSE, .text = "else" };
  }

  if (_is_keyword("==")) {
    _pos += 2;
    return Token{ .type = TokenType::EQUAL, .text = "==" };
  }

  if (_is_keyword("!=")) {
    _pos += 2;
    return Token{ .type = TokenType::NOTEQUAL, .text = "!=" };
  }

  if (_is_keyword("<=")) {
    _pos += 2;
    return Token{ .type = TokenType::LESSEQUAL, .text = "<=" };
  }

  if (_is_keyword(">=")) {
    _pos += 2;
    return Token{ .type = TokenType::GREATEREQUAL, .text = ">=" };
  }

  if (auto res = magic_enum::enum_cast<TokenType>(*_pos); res.has_value()) {
    return Token{ .type = res.value(), .text = std::string{ *_pos++ } };
  }

  if (std::isdigit(*_pos)) {
    return _parse_number();
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
