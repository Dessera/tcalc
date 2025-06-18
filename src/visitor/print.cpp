#include <magic_enum/magic_enum.hpp>
#include <ostream>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/ast/program.hpp"
#include "tcalc/visitor/print.hpp"

namespace tcalc::ast {

PrintVisitor::PrintVisitor(std::ostream& os, std::size_t step)
  : _os{ &os }
  , _step{ step }
{
}

error::Result<void>
PrintVisitor::visit_bin_op(NodePtr<BinaryOpNode>& node)
{
  std::println(
    *_os, "{}{}:", _gen_indent(), magic_enum::enum_name(node->type()));

  _step_indent();
  ret_err(visit(node->left()));
  ret_err(visit(node->right()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_unary_op(NodePtr<UnaryOpNode>& node)
{
  std::println(
    *_os, "{}{}:", _gen_indent(), magic_enum::enum_name(node->type()));

  _step_indent();
  ret_err(visit(node->operand()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_number(NodePtr<NumberNode>& node)
{
  std::println(*_os, "{}NUMBER: {}", _gen_indent(), node->value());
  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_varref(NodePtr<VarRefNode>& node)
{
  std::println(*_os, "{}VARREF: {}", _gen_indent(), node->name());

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_varassign(NodePtr<VarAssignNode>& node)
{
  std::println(*_os, "{}VARASSIGN: {}", _gen_indent(), node->name());

  _step_indent();
  ret_err(visit(node->body()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_fcall(NodePtr<FcallNode>& node)
{
  std::println(*_os, "{}FCALL: {}", _gen_indent(), node->name());
  _step_indent();
  for (auto& arg : node->args()) {
    ret_err(visit(arg));
  }
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_fdef(NodePtr<FdefNode>& node)
{
  std::print(*_os, "{}FDEF: {}:", _gen_indent(), node->name());
  for (auto& arg : node->args()) {
    std::print(*_os, " {}", arg);
  }

  std::println(*_os, "");

  _step_indent();
  ret_err(visit(node->body()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_if(NodePtr<IfNode>& node)
{
  std::println(*_os, "{}IF:", _gen_indent());

  _step_indent();
  ret_err(visit(node->cond()));
  ret_err(visit(node->then()));
  ret_err(visit(node->else_()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_program(NodePtr<ProgramNode>& node)
{
  std::println(*_os, "{}PROGRAM:", _gen_indent());

  _step_indent();
  for (auto& stmt : node->statements()) {
    ret_err(visit(stmt));
  }
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_import(NodePtr<ProgramImportNode>& node)
{
  std::println(*_os, "{}IMPORT: {}", _gen_indent(), node->path());
  return error::ok<void>();
}

}
