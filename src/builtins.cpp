#include <cmath>
#include <vector>

#include "tcalc/builtins.hpp"
#include "tcalc/error.hpp"

namespace tcalc::builtins {

error::Result<double>
sqrt(const std::vector<double>& args, const EvalContext& /*ctx*/)
{
  if (args.size() != 1) {
    return error::err(error::Code::MISMATCHED_ARGS,
                      "Mismatched arguments in sqrt, expected 1, got {}",
                      args.size());
  }

  return error::ok<double>(std::sqrt(args[0]));
}

error::Result<double>
pow(const std::vector<double>& args, const EvalContext& /*ctx*/)
{
  if (args.size() != 2) {
    return error::err(error::Code::MISMATCHED_ARGS,
                      "Mismatched arguments in pow, expected 2, got {}",
                      args.size());
  }

  return error::ok<double>(std::pow(args[0], args[1]));
}

const std::unordered_map<std::string, double> BUILTIN_VARIABLES = {
  { "pi", M_PI },
  { "e", M_E },
};

const std::unordered_map<std::string, Function> BUILTIN_FUNCTIONS = {
  { "sqrt", sqrt },
  { "pow", pow },
};

}
