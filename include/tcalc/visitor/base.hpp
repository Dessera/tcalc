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
#include <type_traits>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/ast/function.hpp"
#include "tcalc/ast/node.hpp"
#include "tcalc/ast/number.hpp"
#include "tcalc/ast/variable.hpp"

namespace tcalc::ast {

/**
 * @brief Base visitor class with any return type.
 *
 * @tparam RT Return type of the visitor.
 */
template<typename RT>
class BaseVisitor
{
public:
  virtual ~BaseVisitor() = default;

  /**
   * @brief Visit a node.
   *
   * @param node Node to visit.
   * @return RT Result of the visit.
   */
  virtual RT visit(std::shared_ptr<Node>& node) = 0;
};

/**
 * @brief Base visitor class with default return type.
 *
 * @tparam RT Return type of the visitor.
 */
template<typename RT>
  requires std::is_default_constructible_v<RT>
class BaseVisitor<RT>
{
public:
  virtual ~BaseVisitor() = default;

  /**
   * @brief Visit a number node.
   *
   * @param node Number node.
   * @return RT Result of the visit.
   */
  virtual RT visit(std::shared_ptr<Node>& node)
  {
    if (auto bin_node = std::dynamic_pointer_cast<BinaryOpNode>(node)) {
      return visit(bin_node);
    }
    if (auto num_node = std::dynamic_pointer_cast<NumberNode>(node)) {
      return visit(num_node);
    }
    if (auto var_node = std::dynamic_pointer_cast<VarRefNode>(node)) {
      return visit(var_node);
    }
    if (auto fcall_node = std::dynamic_pointer_cast<FcallNode>(node)) {
      return visit(fcall_node);
    }
    return RT{};
  }

  /**
   * @brief Visit a binary operation node.
   *
   * @param node Binary operation node.
   * @return RT Result of the visit.
   */
  virtual RT visit(std::shared_ptr<BinaryOpNode>& node)
  {
    if (auto bin_plus_node = std::dynamic_pointer_cast<BinaryPlusNode>(node)) {
      return visit(bin_plus_node);
    }
    if (auto bin_minus_node =
          std::dynamic_pointer_cast<BinaryMinusNode>(node)) {
      return visit(bin_minus_node);
    }
    if (auto bin_multiply_node =
          std::dynamic_pointer_cast<BinaryMultiplyNode>(node)) {
      return visit(bin_multiply_node);
    }
    if (auto bin_divide_node =
          std::dynamic_pointer_cast<BinaryDivideNode>(node)) {
      return visit(bin_divide_node);
    }
    return RT{};
  }

  /**
   * @brief Visit a plus node.
   *
   * @param node Plus node.
   * @return RT Result of the visit.
   */
  virtual RT visit(std::shared_ptr<BinaryPlusNode>& node) = 0;

  /**
   * @brief Visit a minus node.
   *
   * @param node Minus node.
   * @return RT Result of the visit.
   */
  virtual RT visit(std::shared_ptr<BinaryMinusNode>& node) = 0;

  /**
   * @brief Visit a multiply node.
   *
   * @param node Multiply node.
   * @return RT Result of the visit.
   */
  virtual RT visit(std::shared_ptr<BinaryMultiplyNode>& node) = 0;

  /**
   * @brief Visit a divide node.
   *
   * @param node Divide node.
   * @return RT Result of the visit.
   */
  virtual RT visit(std::shared_ptr<BinaryDivideNode>& node) = 0;

  /**
   * @brief Visit a number node.
   *
   * @param node Number node.
   * @return RT Result of the visit.
   */
  virtual RT visit(std::shared_ptr<NumberNode>& node) = 0;

  /**
   * @brief Visit a variable reference node.
   *
   * @param node Variable reference node.
   * @return RT Result of the visit.
   */
  virtual RT visit(std::shared_ptr<VarRefNode>& node) = 0;

  /**
   * @brief Visit a function call node.
   *
   * @param node Function call node.
   * @return RT Result of the visit.
   */
  virtual RT visit(std::shared_ptr<FcallNode>& node) = 0;
};

/**
 * @brief Base visitor class without return type.
 *
 * @tparam void No return type.
 */
template<>
class BaseVisitor<void>
{
public:
  virtual ~BaseVisitor() = default;

  /**
   * @brief Visit a node.
   *
   * @param node Node to visit.
   */
  virtual void visit(std::shared_ptr<Node>& node)
  {
    if (auto bin_node = std::dynamic_pointer_cast<BinaryOpNode>(node)) {
      visit(bin_node);
    }
    if (auto num_node = std::dynamic_pointer_cast<NumberNode>(node)) {
      visit(num_node);
    }
    if (auto var_node = std::dynamic_pointer_cast<VarRefNode>(node)) {
      visit(var_node);
    }
    if (auto fcall_node = std::dynamic_pointer_cast<FcallNode>(node)) {
      visit(fcall_node);
    }
  }

  /**
   * @brief Visit a binary operation node.
   *
   * @param node Binary operation node.
   */
  virtual void visit(std::shared_ptr<BinaryOpNode>& node)
  {
    if (auto bin_plus_node = std::dynamic_pointer_cast<BinaryPlusNode>(node)) {
      visit(bin_plus_node);
    }
    if (auto bin_minus_node =
          std::dynamic_pointer_cast<BinaryMinusNode>(node)) {
      visit(bin_minus_node);
    }
    if (auto bin_multiply_node =
          std::dynamic_pointer_cast<BinaryMultiplyNode>(node)) {
      visit(bin_multiply_node);
    }
    if (auto bin_divide_node =
          std::dynamic_pointer_cast<BinaryDivideNode>(node)) {
      visit(bin_divide_node);
    }
  }

  /**
   * @brief Visit a plus node.
   *
   * @param node Plus node.
   */
  virtual void visit(std::shared_ptr<BinaryPlusNode>& node) = 0;

  /**
   * @brief Visit a minus node.
   *
   * @param node Minus node.
   */
  virtual void visit(std::shared_ptr<BinaryMinusNode>& node) = 0;

  /**
   * @brief Visit a multiply node.
   *
   * @param node Multiply node.
   */
  virtual void visit(std::shared_ptr<BinaryMultiplyNode>& node) = 0;

  /**
   * @brief Visit a divide node.
   *
   * @param node Divide node.
   */
  virtual void visit(std::shared_ptr<BinaryDivideNode>& node) = 0;

  /**
   * @brief Visit a number node.
   *
   * @param node Number node.
   */
  virtual void visit(std::shared_ptr<NumberNode>& node) = 0;

  /**
   * @brief Visit a variable reference node.
   *
   * @param node Variable reference node.
   */
  virtual void visit(std::shared_ptr<VarRefNode>& node) = 0;

  /**
   * @brief Visit a function call node.
   *
   * @param node Function call node.
   */
  virtual void visit(std::shared_ptr<FcallNode>& node) = 0;
};

}
