#include <ostream>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/visitor/print.hpp"

namespace tcalc::ast {

PrintVisitor::PrintVisitor(std::ostream& os, std::size_t step)
  : _os{ &os }
  , _step{ step }
{
}

error::Result<void>
PrintVisitor::visit_bin_plus(std::shared_ptr<BinaryPlusNode>& node)
{
  std::println(*_os, "{}PLUS:", _gen_indent());

  _step_indent();
  ret_err(visit(node->left()));
  ret_err(visit(node->right()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_bin_minus(std::shared_ptr<BinaryMinusNode>& node)
{
  std::println(*_os, "{}MINUS:", _gen_indent());

  _step_indent();
  ret_err(visit(node->left()));
  ret_err(visit(node->right()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_bin_multiply(std::shared_ptr<BinaryMultiplyNode>& node)
{
  std::println(*_os, "{}MULTIPLY:", _gen_indent());

  _step_indent();
  ret_err(visit(node->left()));
  ret_err(visit(node->right()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_bin_divide(std::shared_ptr<BinaryDivideNode>& node)
{
  std::println(*_os, "{}DIVIDE:", _gen_indent());

  _step_indent();
  ret_err(visit(node->left()));
  ret_err(visit(node->right()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_unary_plus(std::shared_ptr<UnaryPlusNode>& node)
{
  std::println(*_os, "{}UNARY_PLUS:", _gen_indent());

  _step_indent();
  ret_err(visit(node->operand()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_unary_minus(std::shared_ptr<UnaryMinusNode>& node)
{
  std::println(*_os, "{}UNARY_MINUS:", _gen_indent());

  _step_indent();
  ret_err(visit(node->operand()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_number(std::shared_ptr<NumberNode>& node)
{
  std::println(*_os, "{}NUMBER: {}", _gen_indent(), node->value());
  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_varref(std::shared_ptr<VarRefNode>& node)
{
  std::println(*_os, "{}VARREF: {}", _gen_indent(), node->name());

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_varassign(std::shared_ptr<VarAssignNode>& node)
{
  std::println(*_os, "{}VARASSIGN: {}", _gen_indent(), node->name());

  _step_indent();
  ret_err(visit(node->body()));
  _unstep_indent();

  return error::ok<void>();
}

error::Result<void>
PrintVisitor::visit_fcall(std::shared_ptr<FcallNode>& node)
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
PrintVisitor::visit_fdef(std::shared_ptr<FdefNode>& node)
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
PrintVisitor::visit_if(std::shared_ptr<IfNode>& node)
{
  std::println(*_os, "{}IF:", _gen_indent());

  _step_indent();
  ret_err(visit(node->cond()));
  ret_err(visit(node->then()));
  ret_err(visit(node->else_()));
  _unstep_indent();

  return error::ok<void>();
}

}
