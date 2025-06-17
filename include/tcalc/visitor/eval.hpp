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

#include <functional>
#include <unordered_map>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/ast/node.hpp"
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
  // avoid undefined reference
private:
  /**
   * @brief Evaluate equality between two double.
   *
   * @param a Left hand side.
   * @param b Right hand side.
   * @return double 1 if equal, 0 if not (a real zero).
   */
  static double _double_eq(double a, double b);

  /**
   * @brief Evaluate equality between two double.
   *
   * @param a Left hand side.
   * @param b Right hand side.
   * @return true if equal
   * @return false if not equal
   */
  static bool _double_eq_bool(double a, double b);

  /**
   * @brief Evaluate inequality between two double.
   *
   * @param a Left hand side.
   * @param b Right hand side.
   * @return double 1 if not equal, 0 if equal (a real zero).
   */
  static double _double_noeq(double a, double b);

  /**
   * @brief Evaluate inequality between two double.
   *
   * @param a Left hand side.
   * @param b Right hand side.
   * @return true if not equal
   * @return false if equal
   */
  static bool _double_noeq_bool(double a, double b);

  /**
   * @brief Forward a double.
   *
   * @param a Double to forward.
   * @return double Forwarded double.
   */
  static double _double_forward(double a);

public:
  inline static const std::unordered_map<NodeType,
                                         std::function<double(double, double)>>
    BINOP_MAP = {
      { NodeType::BINARY_PLUS, std::plus<>() },
      { NodeType::BINARY_MINUS, std::minus<>() },
      { NodeType::BINARY_MULTIPLY, std::multiplies<>() },
      { NodeType::BINARY_DIVIDE, std::divides<>() },
      { NodeType::BINARY_EQUAL, _double_eq },
      { NodeType::BINARY_NOT_EQUAL, _double_noeq },
      { NodeType::BINARY_GREATER, std::greater<>() },
      { NodeType::BINARY_GREATER_EQUAL, std::greater_equal<>() },
      { NodeType::BINARY_LESS, std::less<>() },
      { NodeType::BINARY_LESS_EQUAL, std::less_equal<>() }
    }; /**< Map of binary operator to function. */

  inline static const std::unordered_map<NodeType,
                                         std::function<double(double)>>
    UNARYOP_MAP = {
      { NodeType::UNARY_PLUS, _double_forward },
      { NodeType::UNARY_MINUS, std::negate<>() },
    }; /**< Map of unary operator to function. */

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

  error::Result<double> visit_bin_op(
    std::shared_ptr<BinaryOpNode>& node) override;
  error::Result<double> visit_unary_op(
    std::shared_ptr<UnaryOpNode>& node) override;
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
