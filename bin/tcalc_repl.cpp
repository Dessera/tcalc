#include <iostream>
#include <print>

#include "tcalc/eval.hpp"
int
main()
{
  auto evaluator = tcalc::Evaluator{};

  while (true) {
    std::string line;
    std::print("tcalc> ");
    std::getline(std::cin, line);
    if (line.empty()) {
      break;
    }

    auto res = evaluator.eval(line);
    if (!res.has_value()) {
      res.error().log();
      continue;
    }

    std::println("{}", res.value());
  }
}
