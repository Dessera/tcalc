#include <limits>
#include <vector>

#include "tcalc/builtins.hpp"
#include "tcalc/error.hpp"
#include "tcalc/eval.hpp"
#include "tcalc/visitor/eval.hpp"

namespace tcalc::ast {

EvalVisitor::EvalVisitor(EvalContext& ctx)
  : _ctx{ &ctx }
{
}

error::Result<double>
EvalVisitor::visit_bin_op(std::shared_ptr<BinaryOpNode>& node)
{
  auto lval = unwrap_err(visit(node->left()));
  auto rval = unwrap_err(visit(node->right()));

  return error::ok<double>(BINOP_MAP.at(node->type())(lval, rval));
}

error::Result<double>
EvalVisitor::visit_unary_op(std::shared_ptr<UnaryOpNode>& node)
{
  auto val = unwrap_err(visit(node->operand()));

  return error::ok<double>(UNARYOP_MAP.at(node->type())(val));
}

error::Result<double>
EvalVisitor::visit_number(std::shared_ptr<NumberNode>& node)
{
  return error::ok<double>(node->value());
}

error::Result<double>
EvalVisitor::visit_varref(std::shared_ptr<VarRefNode>& node)
{
  return error::ok<double>(unwrap_err(_ctx->var(node->name())));
}

error::Result<double>
EvalVisitor::visit_varassign(std::shared_ptr<VarAssignNode>& node)
{
  _ctx->var(node->name(), unwrap_err(visit(node->body())));

  return error::ok<double>(unwrap_err(_ctx->var(node->name())));
}

error::Result<double>
EvalVisitor::visit_fcall(std::shared_ptr<FcallNode>& node)
{
  auto func = unwrap_err(_ctx->func(node->name()));

  auto args = std::vector<double>{};
  for (auto& arg : node->args()) {
    args.push_back(unwrap_err(visit(arg)));
  }

  return error::ok<double>(unwrap_err(func(args, *_ctx)));
}

error::Result<double>
EvalVisitor::visit_fdef(std::shared_ptr<FdefNode>& node)
{
  _ctx->func(node->name(), builtins::FunctionWrapper(node));

  return error::ok<double>(0);
}

error::Result<double>
EvalVisitor::visit_if(std::shared_ptr<IfNode>& node)
{
  auto cond = unwrap_err(visit(node->cond()));
  if (_double_noeq_bool(cond, 0)) {
    return visit(node->then());
  }

  return visit(node->else_());
}

double
EvalVisitor::_double_eq(double a, double b)
{
  return _double_eq_bool(a, b);
}

bool
EvalVisitor::_double_eq_bool(double a, double b)
{
  return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

double
EvalVisitor::_double_noeq(double a, double b)
{
  return _double_noeq_bool(a, b);
}

bool
EvalVisitor::_double_noeq_bool(double a, double b)
{
  return std::abs(a - b) > std::numeric_limits<double>::epsilon();
}

double
EvalVisitor::_double_forward(double a)
{
  return a;
}

}
