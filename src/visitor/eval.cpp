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
EvalVisitor::visit_bin_plus(std::shared_ptr<BinaryPlusNode>& node)
{
  auto lval = unwrap_err(visit(node->left()));
  auto rval = unwrap_err(visit(node->right()));
  return error::ok<double>(lval + rval);
}

error::Result<double>
EvalVisitor::visit_bin_minus(std::shared_ptr<BinaryMinusNode>& node)
{
  auto lval = unwrap_err(visit(node->left()));
  auto rval = unwrap_err(visit(node->right()));
  return error::ok<double>(lval - rval);
}

error::Result<double>
EvalVisitor::visit_bin_multiply(std::shared_ptr<BinaryMultiplyNode>& node)
{
  auto lval = unwrap_err(visit(node->left()));
  auto rval = unwrap_err(visit(node->right()));
  return error::ok<double>(lval * rval);
}

error::Result<double>
EvalVisitor::visit_bin_divide(std::shared_ptr<BinaryDivideNode>& node)
{
  auto lval = unwrap_err(visit(node->left()));
  auto rval = unwrap_err(visit(node->right()));
  if (std::abs(rval) < std::numeric_limits<double>::epsilon()) {
    return error::err(error::Code::ZERO_DIVISION, "Division by zero");
  }
  return error::ok<double>(lval / rval);
}

error::Result<double>
EvalVisitor::visit_unary_plus(std::shared_ptr<UnaryPlusNode>& node)
{
  return visit(node->operand());
}

error::Result<double>
EvalVisitor::visit_unary_minus(std::shared_ptr<UnaryMinusNode>& node)
{
  return error::ok<double>(-unwrap_err(visit(node->operand())));
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
  if (std::abs(cond) > std::numeric_limits<double>::epsilon()) {
    return visit(node->then());
  }

  return visit(node->else_());
}

}
