#include "tcalc/error.hpp"
#include "tcalc/parser.hpp"
#include "tcalc/visitor/print.hpp"

int
main()
{
  using tcalc::ast::BaseVisitor;
  using tcalc::ast::Parser;
  using tcalc::ast::PrintVisitor;

  Parser parser{};

  auto ast = parser.parse("1 + 2 * 3 / (4 - 5) + sqrt(9) + pi + e + pow(2, 2)");

  if (!ast.has_value()) {
    ast.error().log();
  }

  auto node = ast.value();

  PrintVisitor pv{};

  pv.BaseVisitor<void>::visit(node);
}