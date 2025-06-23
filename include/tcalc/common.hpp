/**
 * @file common.hpp
 * @author Dessera (dessera@qq.com)
 * @brief tcalc common header.
 * @version 0.1.0
 * @date 2025-06-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_TCALC
#define TCALC_PUBLIC __declspec(dllexport)
#else
#define TCALC_PUBLIC __declspec(dllimport)
#endif
#else
#ifdef BUILDING_TCALC
#define TCALC_PUBLIC __attribute__((visibility("default")))
#else
#define TCALC_PUBLIC
#endif
#endif

#if defined _WIN32 || defined __CYGWIN__
#define TCALC_INLINE inline __forceinline
#else
#define TCALC_INLINE inline __attribute__((always_inline))
#endif

#if defined _WIN32 || defined __CYGWIN__
#define TCALC_PRINTF_FORMAT(fmt_idx, arg_idx)
#else
#define TCALC_PRINTF_FORMAT(fmt_idx, arg_idx)                                  \
  __attribute__((format(printf, fmt_idx, arg_idx)))
#endif
