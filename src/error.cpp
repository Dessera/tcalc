#include <cstdarg>
#include <iostream>
#include <utility>

#include "tcalc/error.hpp"

namespace tcalc::error {

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

  buffer.resize(strlen(buffer.data()));

  return std::unexpected(Error(code, std::move(buffer)));
}

}
