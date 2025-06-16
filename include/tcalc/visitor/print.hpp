/**
 * @file print.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Visitor for printing AST.
 * @version 0.1.0
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/ast/function.hpp"
#include "tcalc/ast/number.hpp"
#include "tcalc/ast/variable.hpp"
#include "tcalc/common.hpp"
#include "tcalc/visitor/base.hpp"

namespace tcalc::ast {

/**
 * @brief Visitor for printing AST.
 *
 */
class TCALC_PUBLIC PrintVisitor : public BaseVisitor<void>
{
public:
  constexpr static std::size_t INDENT_STEP = 2; /**< Default indent step. */

private:
  std::ostream* _os;
  std::size_t _indent{ 0 };
  std::size_t _step;

public:
  /**
   * @brief Construct a new Print Visitor object.
   *
   * @param os Output stream.
   * @param step Indent step.
   */
  PrintVisitor(std::ostream& os = std::cout, std::size_t step = INDENT_STEP);

  ~PrintVisitor() override = default;

  void visit(std::shared_ptr<Node>& node) override;
  void visit(std::shared_ptr<BinaryOpNode>& node) override;
  void visit(std::shared_ptr<BinaryPlusNode>& node) override;
  void visit(std::shared_ptr<BinaryMinusNode>& node) override;
  void visit(std::shared_ptr<BinaryMultiplyNode>& node) override;
  void visit(std::shared_ptr<BinaryDivideNode>& node) override;
  void visit(std::shared_ptr<NumberNode>& node) override;
  void visit(std::shared_ptr<VarRefNode>& node) override;
  void visit(std::shared_ptr<FcallNode>& node) override;

private:
  /**
   * @brief Generate indent string.
   *
   * @return std::string Indent string.
   */
  [[nodiscard]] constexpr auto _gen_indent() const
  {
    return std::string(_indent, ' ');
  }

  /**
   * @brief Step indent.
   *
   */
  constexpr void _step_indent() { _indent += _step; }

  /**
   * @brief Unstep indent.
   *
   */
  constexpr void _unstep_indent() { _indent -= _step; }
};

}
