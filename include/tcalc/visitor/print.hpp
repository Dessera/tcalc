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
#include <ostream>
#include <string>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/ast/function.hpp"
#include "tcalc/ast/node.hpp"
#include "tcalc/ast/number.hpp"
#include "tcalc/ast/variable.hpp"
#include "tcalc/common.hpp"
#include "tcalc/error.hpp"
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
  PrintVisitor(std::ostream& os = std::cout, std::size_t step = INDENT_STEP)
    : _os{ &os }
    , _step{ step }
  {
  }

  ~PrintVisitor() override = default;

  error::Result<void> visit_bin_op(NodePtr<BinaryOpNode>& node) override;
  error::Result<void> visit_unary_op(NodePtr<UnaryOpNode>& node) override;
  error::Result<void> visit_number(NodePtr<NumberNode>& node) override;
  error::Result<void> visit_varref(NodePtr<VarRefNode>& node) override;
  error::Result<void> visit_varassign(NodePtr<VarAssignNode>& node) override;
  error::Result<void> visit_fcall(NodePtr<FcallNode>& node) override;
  error::Result<void> visit_fdef(NodePtr<FdefNode>& node) override;
  error::Result<void> visit_if(NodePtr<IfNode>& node) override;
  error::Result<void> visit_program(NodePtr<ProgramNode>& node) override;
  error::Result<void> visit_import(NodePtr<ProgramImportNode>& node) override;

private:
  /**
   * @brief Generate indent string.
   *
   * @return std::string Indent string.
   */
  [[nodiscard]] TCALC_INLINE auto _gen_indent() const
  {
    return std::string(_indent, ' ');
  }

  /**
   * @brief Step indent.
   *
   */
  TCALC_INLINE void _step_indent() { _indent += _step; }

  /**
   * @brief Unstep indent.
   *
   */
  TCALC_INLINE void _unstep_indent() { _indent -= _step; }
};

}
