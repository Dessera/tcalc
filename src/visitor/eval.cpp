#include <vector>

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
  return error::ok<double>(lval / rval);
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
EvalVisitor::visit_fcall(std::shared_ptr<FcallNode>& node)
{
  auto func = unwrap_err(_ctx->func(node->name()));

  auto args = std::vector<double>{};
  for (auto& arg : node->args()) {
    args.push_back(unwrap_err(visit(arg)));
  }

  return error::ok<double>(unwrap_err(func(args)));
}

}
