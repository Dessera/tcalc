#include <cstddef>
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
  if (rval == 0) {
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
  _ctx->func(node->name(), _create_function(node));

  return error::ok<double>(0);
}

// TODO: Class to handle this
builtins::Function
EvalVisitor::_create_function(std::shared_ptr<FdefNode>& node)
{
  return [node](const std::vector<double>& args,
                const EvalContext& ctx) -> error::Result<double> {
    auto local_ctx = EvalContext{ ctx };
    if (args.size() != node->args().size()) {
      return error::err(error::Code::MISMATCHED_ARGS,
                        "Wrong number of arguments, expected {}, got {}",
                        node->args().size(),
                        args.size());
    }
    for (std::size_t i = 0; i < args.size(); ++i) {
      local_ctx.var(node->args()[i], args[i]);
    }

    auto local_visitor = EvalVisitor{ local_ctx };
    return local_visitor.visit(node->body());
  };
}

}
