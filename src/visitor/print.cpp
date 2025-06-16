#include <ostream>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/visitor/base.hpp"
#include "tcalc/visitor/print.hpp"

namespace tcalc::ast {

PrintVisitor::PrintVisitor(std::ostream& os, std::size_t step)
  : _os{ &os }
  , _step{ step }
{
}

void
PrintVisitor::visit(std::shared_ptr<Node>& node)
{
  BaseVisitor<void>::visit(node);
}

void
PrintVisitor::visit(std::shared_ptr<BinaryOpNode>& node)
{
  BaseVisitor<void>::visit(node);
}

void
PrintVisitor::visit(std::shared_ptr<BinaryPlusNode>& node)
{
  std::println(*_os, "{}PLUS:", _gen_indent());
  _step_indent();
  BaseVisitor<void>::visit(node->left());
  BaseVisitor<void>::visit(node->right());
  _unstep_indent();
}

void
PrintVisitor::visit(std::shared_ptr<BinaryMinusNode>& node)
{
  std::println(*_os, "{}MINUS:", _gen_indent());
  _step_indent();
  BaseVisitor<void>::visit(node->left());
  BaseVisitor<void>::visit(node->right());
  _unstep_indent();
}

void
PrintVisitor::visit(std::shared_ptr<BinaryMultiplyNode>& node)
{
  std::println(*_os, "{}MULTIPLY:", _gen_indent());
  _step_indent();
  BaseVisitor<void>::visit(node->left());
  BaseVisitor<void>::visit(node->right());
  _unstep_indent();
}

void
PrintVisitor::visit(std::shared_ptr<BinaryDivideNode>& node)
{
  std::println(*_os, "{}DIVIDE:", _gen_indent());
  _step_indent();
  BaseVisitor<void>::visit(node->left());
  BaseVisitor<void>::visit(node->right());
  _unstep_indent();
}

void
PrintVisitor::visit(std::shared_ptr<NumberNode>& node)
{
  std::println(*_os, "{}NUMBER: {}", _gen_indent(), node->value());
}

void
PrintVisitor::visit(std::shared_ptr<VarRefNode>& node)
{
  std::println(*_os, "{}VARREF: {}", _gen_indent(), node->name());
}

void
PrintVisitor::visit(std::shared_ptr<FcallNode>& node)
{
  std::println(*_os, "{}FCALL: {}", _gen_indent(), node->name());
  _step_indent();
  for (auto& arg : node->args()) {
    BaseVisitor<void>::visit(arg);
  }
  _unstep_indent();
}

}
