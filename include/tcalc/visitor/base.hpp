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
#include "tcalc/ast/control_flow.hpp"
#include "tcalc/ast/function.hpp"
#include "tcalc/ast/node.hpp"
#include "tcalc/ast/number.hpp"
#include "tcalc/ast/unaryop.hpp"
#include "tcalc/ast/variable.hpp"
#include "tcalc/error.hpp"

#define __check_node_type(node, type, entry)                                   \
  if (auto node_type = std::dynamic_pointer_cast<type>(node)) {                \
    return entry(node_type);                                                   \
  }

#define VISIT_DEFAULT(node)                                                    \
  {                                                                            \
    (void)node;                                                                \
    return error::ok<RT>();                                                    \
  }

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
    __check_node_type(node, BinaryOpNode, visit_bin_op);
    __check_node_type(node, UnaryOpNode, visit_unary_op);
    __check_node_type(node, NumberNode, visit_number);
    __check_node_type(node, VarRefNode, visit_varref);
    __check_node_type(node, VarAssignNode, visit_varassign);
    __check_node_type(node, FcallNode, visit_fcall);
    __check_node_type(node, FdefNode, visit_fdef);
    __check_node_type(node, IfNode, visit_if);

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
    __check_node_type(node, BinaryPlusNode, visit_bin_plus);
    __check_node_type(node, BinaryMinusNode, visit_bin_minus);
    __check_node_type(node, BinaryMultiplyNode, visit_bin_multiply);
    __check_node_type(node, BinaryDivideNode, visit_bin_divide);
    __check_node_type(node, BinaryEqualNode, visit_bin_equal);
    __check_node_type(node, BinaryNotEqualNode, visit_bin_notequal);
    __check_node_type(node, BinaryGreaterNode, visit_bin_greater);
    __check_node_type(node, BinaryGreaterEqualNode, visit_bin_greaterequal);
    __check_node_type(node, BinaryLessNode, visit_bin_less);
    __check_node_type(node, BinaryLessEqualNode, visit_bin_lessequal);

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
    __check_node_type(node, UnaryPlusNode, visit_unary_plus);
    __check_node_type(node, UnaryMinusNode, visit_unary_minus);

    return error::ok<RT>();
  }

  /**
   * @brief Visit a plus node.
   *
   * @param node Plus node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_plus(
    std::shared_ptr<BinaryPlusNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a minus node.
   *
   * @param node Minus node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_minus(
    std::shared_ptr<BinaryMinusNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a multiply node.
   *
   * @param node Multiply node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_multiply(
    std::shared_ptr<BinaryMultiplyNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a divide node.
   *
   * @param node Divide node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_divide(
    std::shared_ptr<BinaryDivideNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a equal node.
   *
   * @param node Equal node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_equal(
    std::shared_ptr<BinaryEqualNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a not equal node.
   *
   * @param node Not equal node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_notequal(
    std::shared_ptr<BinaryNotEqualNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a greater node.
   *
   * @param node Greater node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_greater(
    std::shared_ptr<BinaryGreaterNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a greater equal node.
   *
   * @param node Greater equal node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_greaterequal(
    std::shared_ptr<BinaryGreaterEqualNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a less node.
   *
   * @param node Less node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_less(
    std::shared_ptr<BinaryLessNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a less equal node.
   *
   * @param node Less equal node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_bin_lessequal(
    std::shared_ptr<BinaryLessEqualNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a unary plus node.
   *
   * @param node Unary plus node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_unary_plus(
    std::shared_ptr<UnaryPlusNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a unary minus node.
   *
   * @param node Unary minus node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_unary_minus(
    std::shared_ptr<UnaryMinusNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a number node.
   *
   * @param node Number node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_number(std::shared_ptr<NumberNode>& node)
    VISIT_DEFAULT(node);

  /**
   * @brief Visit a variable reference node.
   *
   * @param node Variable reference node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_varref(std::shared_ptr<VarRefNode>& node)
    VISIT_DEFAULT(node);

  /**
   * @brief Visit a variable assignment node.
   *
   * @param node Variable assignment node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_varassign(
    std::shared_ptr<VarAssignNode>& node) VISIT_DEFAULT(node);

  /**
   * @brief Visit a function call node.
   *
   * @param node Function call node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_fcall(std::shared_ptr<FcallNode>& node)
    VISIT_DEFAULT(node);

  /**
   * @brief Visit a function definition node.
   *
   * @param node Function definition node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_fdef(std::shared_ptr<FdefNode>& node)
    VISIT_DEFAULT(node);

  /**
   * @brief Visit an if node.
   *
   * @param node If node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_if(std::shared_ptr<IfNode>& node)
    VISIT_DEFAULT(node);
};

}
