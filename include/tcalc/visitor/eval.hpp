/**
 * @file eval.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Visitor for evaluating AST.
 * @version 0.1.0
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include "tcalc/builtins.hpp"
#include "tcalc/common.hpp"
#include "tcalc/eval.hpp"
#include "tcalc/visitor/base.hpp"

namespace tcalc::ast {

/**
 * @brief Visitor for evaluating AST.
 *
 */
class TCALC_PUBLIC EvalVisitor : public BaseVisitor<double>
{
private:
  EvalContext* _ctx;

public:
  /**
   * @brief Construct a new Eval Visitor object.
   *
   * @param ctx Evaluation context.
   */
  EvalVisitor(EvalContext& ctx);

  ~EvalVisitor() override = default;

  error::Result<double> visit_bin_plus(
    std::shared_ptr<BinaryPlusNode>& node) override;
  error::Result<double> visit_bin_minus(
    std::shared_ptr<BinaryMinusNode>& node) override;
  error::Result<double> visit_bin_multiply(
    std::shared_ptr<BinaryMultiplyNode>& node) override;
  error::Result<double> visit_bin_divide(
    std::shared_ptr<BinaryDivideNode>& node) override;
  error::Result<double> visit_unary_plus(
    std::shared_ptr<UnaryPlusNode>& node) override;
  error::Result<double> visit_unary_minus(
    std::shared_ptr<UnaryMinusNode>& node) override;
  error::Result<double> visit_number(
    std::shared_ptr<NumberNode>& node) override;
  error::Result<double> visit_varref(
    std::shared_ptr<VarRefNode>& node) override;
  error::Result<double> visit_varassign(
    std::shared_ptr<VarAssignNode>& node) override;
  error::Result<double> visit_fcall(std::shared_ptr<FcallNode>& node) override;
  error::Result<double> visit_fdef(std::shared_ptr<FdefNode>& node) override;
  error::Result<double> visit_if(std::shared_ptr<IfNode>& node) override;
};

}
