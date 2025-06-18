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

    if (line == "exit") {
      break;
    }

    auto res = evaluator.eval_prog(line);
    if (!res.has_value()) {
      res.error().log();
      continue;
    }

    auto res_value = res.value();
    for (auto v : res_value) {
      std::println("{}", v);
    }
  }
}
