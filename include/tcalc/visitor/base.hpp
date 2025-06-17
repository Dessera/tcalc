/**
 * @file base.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Base visitor class.
 * @version 0.1.0
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <memory>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/ast/function.hpp"
#include "tcalc/ast/node.hpp"
#include "tcalc/ast/number.hpp"
#include "tcalc/ast/unaryop.hpp"
#include "tcalc/ast/variable.hpp"
#include "tcalc/error.hpp"

namespace tcalc::ast {

/**
 * @brief Base visitor class with default return type.
 *
 * @tparam RT Return type of the visitor.
 */
template<typename RT>
class BaseVisitor
{
public:
  virtual ~BaseVisitor() = default;

  /**
   * @brief Visit a number node.
   *
   * @param node Number node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit(std::shared_ptr<Node>& node)
  {
    if (auto bin_node = std::dynamic_pointer_cast<BinaryOpNode>(node)) {
      return visit_bin_op(bin_node);
    }
    if (auto unary_node = std::dynamic_pointer_cast<UnaryOpNode>(node)) {
      return visit_unary_op(unary_node);
    }
    if (auto num_node = std::dynamic_pointer_cast<NumberNode>(node)) {
      return visit_number(num_node);
    }
    if (auto var_node = std::dynamic_pointer_cast<VarRefNode>(node)) {
      return visit_varref(var_node);
    }
    if (auto fcall_node = std::dynamic_pointer_cast<FcallNode>(node)) {
      return visit_fcall(fcall_node);
    }
    if (auto fdef_node = std::dynamic_pointer_cast<FdefNode>(node)) {
      return visit_fdef(fdef_node);
    }

    return error::ok<RT>();
  }

  /**
   * @brief Visit a binary operation node.
   *
   * @param node Binary operation node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_op(std::shared_ptr<BinaryOpNode>& node)
  {
    if (auto bin_plus_node = std::dynamic_pointer_cast<BinaryPlusNode>(node)) {
      return visit_bin_plus(bin_plus_node);
    }
    if (auto bin_minus_node =
          std::dynamic_pointer_cast<BinaryMinusNode>(node)) {
      return visit_bin_minus(bin_minus_node);
    }
    if (auto bin_multiply_node =
          std::dynamic_pointer_cast<BinaryMultiplyNode>(node)) {
      return visit_bin_multiply(bin_multiply_node);
    }
    if (auto bin_divide_node =
          std::dynamic_pointer_cast<BinaryDivideNode>(node)) {
      return visit_bin_divide(bin_divide_node);
    }

    return error::ok<RT>();
  }

  /**
   * @brief Visit a unary operation node.
   *
   * @param node Unary operation node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_unary_op(std::shared_ptr<UnaryOpNode>& node)
  {
    if (auto unary_plus_node = std::dynamic_pointer_cast<UnaryPlusNode>(node)) {
      return visit_unary_plus(unary_plus_node);
    }
    if (auto unary_minus_node =
          std::dynamic_pointer_cast<UnaryMinusNode>(node)) {
      return visit_unary_minus(unary_minus_node);
    }

    return error::ok<RT>();
  }

  /**
   * @brief Visit a plus node.
   *
   * @param node Plus node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_plus(
    std::shared_ptr<BinaryPlusNode>& node) = 0;

  /**
   * @brief Visit a minus node.
   *
   * @param node Minus node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_minus(
    std::shared_ptr<BinaryMinusNode>& node) = 0;

  /**
   * @brief Visit a multiply node.
   *
   * @param node Multiply node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_multiply(
    std::shared_ptr<BinaryMultiplyNode>& node) = 0;

  /**
   * @brief Visit a divide node.
   *
   * @param node Divide node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_divide(
    std::shared_ptr<BinaryDivideNode>& node) = 0;

  /**
   * @brief Visit a unary plus node.
   *
   * @param node Unary plus node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_unary_plus(
    std::shared_ptr<UnaryPlusNode>& node) = 0;

  /**
   * @brief Visit a unary minus node.
   *
   * @param node Unary minus node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_unary_minus(
    std::shared_ptr<UnaryMinusNode>& node) = 0;

  /**
   * @brief Visit a number node.
   *
   * @param node Number node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_number(std::shared_ptr<NumberNode>& node) = 0;

  /**
   * @brief Visit a variable reference node.
   *
   * @param node Variable reference node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_varref(std::shared_ptr<VarRefNode>& node) = 0;

  /**
   * @brief Visit a function call node.
   *
   * @param node Function call node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_fcall(std::shared_ptr<FcallNode>& node) = 0;

  /**
   * @brief Visit a function definition node.
   *
   * @param node Function definition node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_fdef(std::shared_ptr<FdefNode>& node) = 0;
};

}
