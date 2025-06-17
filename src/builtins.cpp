#include <cmath>
#include <utility>
#include <vector>

#include "tcalc/ast/function.hpp"
#include "tcalc/builtins.hpp"
#include "tcalc/error.hpp"
#include "tcalc/eval.hpp"
#include "tcalc/visitor/eval.hpp"

namespace tcalc::builtins {

FunctionWrapper::FunctionWrapper(std::shared_ptr<ast::FdefNode> node)
  : _node{ std::move(node) }
{
}

error::Result<double>
FunctionWrapper::operator()(const std::vector<double>& args,
                            const EvalContext& ctx) const
{
  auto local_ctx = ctx;
  if (args.size() != _node->args().size()) {
    return error::err(error::Code::MISMATCHED_ARGS,
                      "Wrong number of arguments, expected {}, got {}",
                      _node->args().size(),
                      args.size());
  }
  for (std::size_t i = 0; i < args.size(); ++i) {
    local_ctx.var(_node->args()[i], args[i]);
  }

  auto local_visitor = ast::EvalVisitor{ local_ctx };
  return local_visitor.visit(_node->body());
}

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
