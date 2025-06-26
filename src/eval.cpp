#include "tcalc/eval.hpp"
#include "tcalc/builtins.hpp"
#include "tcalc/error.hpp"
#include "tcalc/visitor/eval.hpp"

namespace tcalc {

error::Result<double>
EvalContext::var(const std::string& name) const
{
  if (_vars.contains(name)) {
    return _vars.at(name);
  }

  return error::err(
    error::Code::UNDEFINED_VAR, "Undefined variable: %s", name.c_str());
}

error::Result<builtins::Function>
EvalContext::func(const std::string& name) const
{
  if (_funcs.contains(name)) {
    return _funcs.at(name);
  }

  return error::err(
    error::Code::UNDEFINED_FUNC, "Undefined function: %s", name.c_str());
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
