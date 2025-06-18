#include "tcalc/eval.hpp"
#include "tcalc/builtins.hpp"
#include "tcalc/error.hpp"
#include "tcalc/visitor/eval.hpp"

namespace tcalc {

EvalContext::EvalContext(
  std::unordered_map<std::string, double> vars,
  std::unordered_map<std::string, builtins::Function> funcs,
  std::size_t call_depth)
  : _vars{ std::move(vars) }
  , _funcs{ std::move(funcs) }
  , _call_depth{ call_depth }
{
}

error::Result<double>
EvalContext::var(const std::string& name) const
{
  if (_vars.contains(name)) {
    return _vars.at(name);
  }

  return error::err(error::Code::UNDEFINED_VAR, "Undefined variable: {}", name);
}

error::Result<builtins::Function>
EvalContext::func(const std::string& name) const
{
  if (_funcs.contains(name)) {
    return _funcs.at(name);
  }

  return error::err(
    error::Code::UNDEFINED_FUNC, "Undefined function: {}", name);
}

void
EvalContext::update_with(const EvalContext& ctx)
{
  _vars.insert(ctx._vars.begin(), ctx._vars.end());
  _funcs.insert(ctx._funcs.begin(), ctx._funcs.end());
}

Evaluator::Evaluator(const EvalContext& ctx)
  : _ctx{ ctx }
{
  _ctx.var("ans", 1);
}

Evaluator::Evaluator()
  : Evaluator{ EvalContext{ builtins::BUILTIN_VARIABLES,
                            builtins::BUILTIN_FUNCTIONS } }
{
}

error::Result<double>
Evaluator::eval(std::string_view input)
{
  auto node = unwrap_err(_parser.parse(input));

  auto visitor = ast::EvalVisitor{ _ctx };
  auto res = unwrap_err(visitor.visit(node));

  _ctx.var("ans", res);

  return res;
}

error::Result<std::vector<double>>
Evaluator::eval_prog(std::string_view input)
{
  auto nodes = unwrap_err(_parser.parse(input));
  auto visitor = ast::ProgramEvalVisitor{ _ctx };

  auto res = unwrap_err(visitor.visit(nodes));

  if (res.size() > 0) {
    _ctx.var("ans", res.back());
  }

  return res;
}

}
