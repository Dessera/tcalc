#include <magic_enum/magic_enum.hpp>

#include "tcalc/token.hpp"

namespace tcalc::token {

std::string_view
token_type_to_string(TokenType type)
{
  return magic_enum::enum_name(type);
}

}
