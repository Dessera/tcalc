#include <cstdarg>
#include <iostream>
#include <utility>

#include "tcalc/error.hpp"

namespace tcalc::error {

const std::unordered_map<Code, std::string> CODE_NAMES = {
  { Code::SYNTAX_ERROR, "SYNAX_ERROR" },
  { Code::UNDEFINED_VAR, "UNDEFINED_VAR" },
  { Code::UNDEFINED_FUNC, "UNDEFINED_FUNC" },
  { Code::MISMATCHED_ARGS, "MISMATCHED_ARGS" },
  { Code::ZERO_DIVISION, "ZERO_DIVISION" },
  { Code::RECURSION_LIMIT, "RECURSION_LIMIT" },
  { Code::FILE_NOT_FOUND, "FILE_NOT_FOUND" },
};

Error::Error(Code code, std::string msg) noexcept
  : _code{ code }
  , _msg{ std::move(msg) }
{
}

void
Error::log() const noexcept
{
  std::cerr << "Exception occurred: " << _msg << " [" << CODE_NAMES.at(_code)
            << "]\n";
}

std::unexpected<Error>
err(Code code, const char* fmt, ...) noexcept
{
  auto buffer = std::string{};
  buffer.resize(Error::MAX_MSG_LEN);

  va_list args;
  va_start(args, fmt); // NOLINT

  std::vsnprintf(buffer.data(), buffer.size(), fmt, args); // NOLINT

  va_end(args); // NOLINT

  return std::unexpected(Error(code, std::move(buffer)));
}

}
