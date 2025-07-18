/**
 * @file error.hpp
 * @author Dessera (dessera@qq.com)
 * @brief tcalc error definition.
 * @version 0.2.0
 * @date 2025-06-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <string>
#include <unordered_map>

#ifdef TCALC_USE_TL_EXPECTED
#include <tl/expected.hpp>
#define _TCALC_EXPECTED_NS tl
#else
#include <expected>
#define _TCALC_EXPECTED_NS std
#endif

#include "tcalc/common.hpp"

#define ret_err(expr)                                                          \
  if (auto res = (expr); !res.has_value()) {                                   \
    return _TCALC_EXPECTED_NS::unexpected(res.error());                        \
  }

#define unwrap_err(expr)                                                       \
  ({                                                                           \
    auto _ret = (expr);                                                        \
    if (!_ret.has_value()) {                                                   \
      return _TCALC_EXPECTED_NS::unexpected(_ret.error());                     \
    }                                                                          \
    _ret.value();                                                              \
  })

#define log_err(expr)                                                          \
  {                                                                            \
    auto _ret = (expr);                                                        \
    if (!_ret.has_value()) {                                                   \
      _ret.error().log();                                                      \
    }                                                                          \
  }

#define log_err_exit(expr)                                                     \
  {                                                                            \
    auto _ret = (expr);                                                        \
    if (!_ret.has_value()) {                                                   \
      _ret.error().log();                                                      \
      std::exit(EXIT_FAILURE);                                                 \
    }                                                                          \
  }

namespace tcalc::error {

/**
 * @brief Error code.
 *
 */
enum class Code : uint8_t
{
  SYNTAX_ERROR,    /**< Syntax error in tokenizer and parser. */
  UNDEFINED_VAR,   /**< Undefined variable. */
  UNDEFINED_FUNC,  /**< Undefined function. */
  MISMATCHED_ARGS, /**< Mismatched arguments. */
  ZERO_DIVISION,   /**< Division by zero. */
  RECURSION_LIMIT, /**< Recursion limit exceeded. */
  FILE_NOT_FOUND,  /**< File not found. */
};

inline const std::unordered_map<Code, std::string> CODE_NAMES = {
  { Code::SYNTAX_ERROR, "SYNAX_ERROR" },
  { Code::UNDEFINED_VAR, "UNDEFINED_VAR" },
  { Code::UNDEFINED_FUNC, "UNDEFINED_FUNC" },
  { Code::MISMATCHED_ARGS, "MISMATCHED_ARGS" },
  { Code::ZERO_DIVISION, "ZERO_DIVISION" },
  { Code::RECURSION_LIMIT, "RECURSION_LIMIT" },
  { Code::FILE_NOT_FOUND, "FILE_NOT_FOUND" },
}; /**< Error code names. */

/**
 * @brief Error class.
 *
 */
class TCALC_PUBLIC Error : public std::exception
{
public:
  constexpr static std::size_t MAX_MSG_LEN = 256; /**< Max message length. */

private:
  Code _code;
  std::string _msg;

public:
  /**
   * @brief Construct a new Error object (should be noexcept in semantic).
   *
   * @param code Error code.
   * @param msg  Error message.
   */
  Error(Code code, std::string msg) noexcept
    : _code{ code }
    , _msg{ std::move(msg) }
  {
  }

  /**
   * @brief Get error code.
   *
   * @return Error code.
   */
  [[nodiscard]] TCALC_INLINE auto code() const noexcept { return _code; }

  /**
   * @brief Get error message.
   *
   * @return Error message.
   */
  [[nodiscard]] TCALC_INLINE const auto& msg() const noexcept { return _msg; }

  /**
   * @brief Log error message to stderr (should be noexcept in semantic).
   *
   */
  void log() const noexcept;

  /**
   * @brief Get error message.
   *
   * @return const char* Error message.
   */
  [[nodiscard]] const char* what() const noexcept override
  {
    return _msg.c_str();
  }
};

/**
 * @brief Result type.
 *
 * @tparam T Return type.
 */
template<typename T>
using Result = _TCALC_EXPECTED_NS::expected<T, Error>;

/**
 * @brief Create an error.
 *
 * @param code Error code.
 * @param message Error message.
 * @return Result<T> Error.
 */
TCALC_INLINE auto
err(Code code, const std::string& message) noexcept
{
  return _TCALC_EXPECTED_NS::unexpected(Error(code, message));
}

/**
 * @brief Create a raw error with errno.
 *
 * @param code Error code.
 * @return Error Raw error.
 */
TCALC_INLINE auto
raw_err(Code code) noexcept
{
  auto errno_copy = errno;
  return Error(code,
               errno_copy == 0 ? "Unknown error" : std::strerror(errno_copy));
}

/**
 * @brief Create an error with errno.
 *
 * @param code Error code.
 * @return Result<T> Error.
 */
TCALC_INLINE auto
err(Code code) noexcept
{
  return _TCALC_EXPECTED_NS::unexpected(raw_err(code));
}

/**
 * @brief Create an error with format.
 *
 * @param code Error code.
 * @param fmt Format string.
 * @param args Arguments.
 * @return Result<T> Error.
 * @note To prevent using <format> or <print> headers, this function uses
 * std::vsnprintf.
 */
TCALC_PRINTF_FORMAT(2, 3)
_TCALC_EXPECTED_NS::unexpected<Error>
err(Code code, const char* fmt, ...) noexcept;

/**
 * @brief Create a result with value.
 *
 * @tparam T Return type.
 * @tparam Args Arguments to construct the value.
 * @param args Arguments to construct the value.
 * @return Result<T> Result.
 */
template<typename T, typename... Args>
TCALC_INLINE auto
ok(Args&&... args) noexcept
{
  return _TCALC_EXPECTED_NS::expected<T, Error>(T(std::forward<Args>(args)...));
}

/**
 * @brief Create a result with void value.
 *
 * @return Result<void> Result.
 */
template<>
TCALC_INLINE auto
ok<void>() noexcept
{
  return _TCALC_EXPECTED_NS::expected<void, Error>();
}

}
