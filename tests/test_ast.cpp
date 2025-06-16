#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <sstream>

#include "tcalc/parser.hpp"
#include "tcalc/visitor/print.hpp"

namespace {

std::string
parse_ast(std::string_view input)
{
  using tcalc::ast::Parser;
  using tcalc::ast::PrintVisitor;

  auto parser = Parser{};
  auto res = parser.parse(input);
  REQUIRE(res.has_value());

  auto node = res.value();
  auto ss = std::stringstream{};
  auto visitor = PrintVisitor{ ss };

  REQUIRE(visitor.visit(node).has_value());

  return ss.str();
}

}

TEST_CASE("Test AST Parser", "[ast][parser][success]")
{
  using tcalc::ast::Parser;
  using tcalc::ast::PrintVisitor;

  std::string expected_parsed = ("MINUS:\n"
                                 "  PLUS:\n"
                                 "    NUMBER: 2\n"
                                 "    DIVIDE:\n"
                                 "      MULTIPLY:\n"
                                 "        NUMBER: 2\n"
                                 "        VARREF: pi\n"
                                 "      FCALL: sqrt\n"
                                 "        NUMBER: 2\n"
                                 "  NUMBER: 1\n");

  auto real_parsed = parse_ast("2 + 2 * pi / sqrt(2) - 1");

  REQUIRE(real_parsed == expected_parsed);
}

TEST_CASE("Test AST Parser Errors", "[ast][parser][error]")
{
  using tcalc::ast::Parser;

  auto parser = Parser{};

  auto res1 = parser.parse("22aa");
  REQUIRE_FALSE(res1.has_value());

  auto res2 = parser.parse("2 **// 2");
  REQUIRE_FALSE(res2.has_value());

  auto res3 = parser.parse("2 + 2 * pi / sqrt(2) - 1 +");
  REQUIRE_FALSE(res3.has_value());
}
