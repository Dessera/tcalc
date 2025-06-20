#include <cmath>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>

#include "tcalc/ast/function.hpp"
#include "tcalc/ast/program.hpp"
#include "tcalc/builtins.hpp"
#include "tcalc/error.hpp"
#include "tcalc/eval.hpp"
#include "tcalc/visitor/eval.hpp"

namespace tcalc::builtins {

FunctionWrapper::FunctionWrapper(ast::NodePtr<ast::FdefNode> node)
  : _node{ std::move(node) }
{
}

error::Result<double>
FunctionWrapper::operator()(const std::vector<double>& args,
                            const EvalContext& ctx) const
{
  auto local_ctx = ctx;
  local_ctx.increment_call_depth();

  if (local_ctx.call_depth() >= EvalContext::MAX_CALL_DEPTH) {
    return error::err(error::Code::RECURSION_LIMIT,
                      "Function call `{}' exceeded maximum recursion depth",
                      _node->name());
  }

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

ImportWrapper::ImportWrapper(ast::NodePtr<ast::ProgramImportNode> node)
  : _node{ std::move(node) }
{
}

error::Result<void>
ImportWrapper::import(EvalContext& ctx) const
{
  auto file = std::ifstream{ _node->path() };
  if (!file.is_open()) {
    return error::err(
      error::Code::FILE_NOT_FOUND, "File `{}` not found", _node->path());
  }

  auto iss = std::stringstream{};
  iss << file.rdbuf();

  auto evaluator = Evaluator{};
  ret_err(evaluator.eval_prog(iss.str()));

  ctx.update_with(evaluator.ctx());

  return error::ok<void>();
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

error::Result<double>
log(const std::vector<double>& args, const EvalContext& /*ctx*/)
{
  if (args.size() != 2) {
    return error::err(error::Code::MISMATCHED_ARGS,
                      "Mismatched arguments in log, expected 2, got {}",
                      args.size());
  }

  return error::ok<double>(std::log(args[1]) / std::log(args[0]));
}

const std::unordered_map<std::string, double> BUILTIN_VARIABLES = {
  { "pi", M_PI },
  { "e", M_E },
};

const std::unordered_map<std::string, Function> BUILTIN_FUNCTIONS = {
  { "sqrt", sqrt },
  { "pow", pow },
  { "log", log },
};

}
