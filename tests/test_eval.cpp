#include "tcalc/eval.hpp"
#include <print>

int
main()
{
  tcalc::Evaluator eval;

  auto res = eval.eval("2 + 2");
  if (res.has_value()) {
    std::println("2 + 2 = {}", res.value());
  } else {
    res.error().log();
  }

  auto res2 = eval.eval("1 + 2 * 3.0 / (4 - 5) + sqrt(9) + pi + e + pow(2, 2)");
  if (res2.has_value()) {
    std::println("1 + 2 * 3.0 / (4 - 5) + sqrt(9) + pi + e + pow(2, 2) = {}",
                 res2.value());
  } else {
    res2.error().log();
  }

  auto res3 = eval.eval("1 + 2 * 3 / invalid + invalid_func(42)");
  if (res3.has_value()) {
    std::println("1 + 2 * 3 / invalid + invalid_func(42) = {}", res3.value());
  } else {
    res3.error().log();
  }
}
