#include <ostream>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/ast/node.hpp"
#include "tcalc/ast/program.hpp"
#include "tcalc/visitor/print.hpp"

namespace tcalc::ast {

error::Result<void>
PrintVisitor::visit_bin_op(NodePtr<BinaryOpNode>& node)
{
  *_os << _gen_indent() << NODE_TYPE_NAMES.at(node->type()) << ":\n";

  _step_indent();
  ret_err(visit(node->left()));
  ret_err(visit(node->right()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_unary_op(NodePtr<UnaryOpNode>& node)
{
  *_os << _gen_indent() << NODE_TYPE_NAMES.at(node->type()) << ":\n";

  _step_indent();
  ret_err(visit(node->operand()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_number(NodePtr<NumberNode>& node)
{
  *_os << _gen_indent() << "NUMBER: " << node->value() << ":\n";
  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_varref(NodePtr<VarRefNode>& node)
{
  *_os << _gen_indent() << "VARREF: " << node->name() << ":";

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_varassign(NodePtr<VarAssignNode>& node)
{
  *_os << _gen_indent() << "VARASSIGN: " << node->name() << ":\n";

  _step_indent();
  ret_err(visit(node->body()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_fcall(NodePtr<FcallNode>& node)
{
  *_os << _gen_indent() << "FCALL: " << node->name() << ":\n";
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
  *_os << _gen_indent() << "FDEF: " << node->name() << ":";
  for (auto& arg : node->args()) {
    *_os << " " << arg;
  }

  *_os << "\n";

  _step_indent();
  ret_err(visit(node->body()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_if(NodePtr<IfNode>& node)
{
  *_os << _gen_indent() << "IF:\n";

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
  *_os << _gen_indent() << "PROGRAM:\n";

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
  *_os << _gen_indent() << "IMPORT: " << node->path() << ":\n";
  return error::ok<void>();
}

}
