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
    VISIT_DEFAULT(node);

  /**
   * @brief Visit a unary operation node.
   *
   * @param node Unary operation node.
   * @return error::Result<RT> Result of the visit.
   */
  virtual error::Result<RT> visit_unary_op(std::shared_ptr<UnaryOpNode>& node)
    VISIT_DEFAULT(node);

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
