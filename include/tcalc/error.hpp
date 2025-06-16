/**
 * @file error.hpp
 * @author Dessera (dessera@qq.com)
 * @brief tcalc error definition.
 * @version 0.1.0
 * @date 2025-06-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cstdint>
#include <cstring>
#include <exception>
#include <expected>
#include <format>
#include <string>

#include "tcalc/common.hpp"

#define ret_err(expr)                                                          \
  if (auto res = (expr); !res.has_value()) {                                   \
    return std::unexpected(res.error());                                       \
  }

#define unwrap_err(expr)                                                       \
  ({                                                                           \
    auto _ret = (expr);                                                        \
    if (!_ret.has_value()) {                                                   \
      return std::unexpected(_ret.error());                                    \
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
};

/**
 * @brief Error class.
 *
 */
class TCALC_PUBLIC Error : public std::exception
{
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
  Error(Code code, std::string msg) noexcept;

  /**
   * @brief Get error code.
   *
   * @return Error code.
   */
  [[nodiscard]] constexpr auto code() const noexcept { return _code; }

  /**
   * @brief Get error message.
   *
   * @return Error message.
   */
  [[nodiscard]] constexpr const auto& msg() const noexcept { return _msg; }

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
using Result = std::expected<T, Error>;

/**
 * @brief Create an error.
 *
 * @param code Error code.
 * @param message Error message.
 * @return Result<T> Error.
 */
constexpr auto
err(Code code, const std::string& message) noexcept
{
  return std::unexpected(Error(code, message));
}

/**
 * @brief Create a raw error with errno.
 *
 * @param code Error code.
 * @return Error Raw error.
 */
constexpr auto
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
constexpr auto
err(Code code) noexcept
{
  return std::unexpected(raw_err(code));
}

/**
 * @brief Create an error with format string.
 *
 * @tparam Args Format string arguments.
 * @param code Error code.
 * @param fmt Format string.
 * @param args Format string arguments.
 * @return Result<T> Error.
 */
template<typename... Args>
constexpr auto
err(Code code, std::format_string<Args...> fmt, Args&&... args) noexcept
{
  return std::unexpected(
    Error(code, std::format(fmt, std::forward<Args>(args)...)));
}

/**
 * @brief Create a result with value.
 *
 * @tparam T Return type.
 * @tparam Args Arguments to construct the value.
 * @param args Arguments to construct the value.
 * @return Result<T> Result.
 */
template<typename T, typename... Args>
constexpr auto
ok(Args&&... args) noexcept
{
  return std::expected<T, Error>(T(std::forward<Args>(args)...));
}

/**
 * @brief Create a result with void value.
 *
 * @return Result<void> Result.
 */
template<>
constexpr auto
ok<void>() noexcept
{
  return std::expected<void, Error>();
}

}
