#include <iostream>
#include <utility>

#include "magic_enum/magic_enum.hpp"
#include "tcalc/error.hpp"

namespace tcalc::error {

Error::Error(Code code, std::string msg) noexcept
  : _code{ code }
  , _msg{ std::move(msg) }
{
}

void
Error::log() const noexcept
{
  std::cerr << "Exception occurred: " << _msg << " ["
            << magic_enum::enum_name(_code) << "]\n";
}

}
