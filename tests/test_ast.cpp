#include <gtest/gtest.h>
#include <tcalc/parser.hpp>

namespace {

TEST(ParserTest, Expression)
{
  auto parser = tcalc::ast::Parser{};

  auto res = parser.parse("1 + 2 * 3 / sqrt(pow(3, 2)) - pi");
  EXPECT_TRUE(res.has_value());
}

TEST(ParserTest, FuncDefinition)
{
  auto parser = tcalc::ast::Parser{};

  auto res = parser.parse("def f(x) x + 1");
  EXPECT_TRUE(res.has_value());
}

TEST(ParserTest, VarDefinition)
{
  auto parser = tcalc::ast::Parser{};

  auto res = parser.parse("let x = 1");
  EXPECT_TRUE(res.has_value());
}

TEST(ParserTest, IfStatement)
{
  auto parser = tcalc::ast::Parser{};

  auto res = parser.parse("if x > 0 then x + 1 else x - 1");
  EXPECT_TRUE(res.has_value());
}

TEST(ParserTest, ImportStatement)
{
  auto parser = tcalc::ast::Parser{};

  auto res = parser.parse("import math");
  EXPECT_TRUE(res.has_value());
}

TEST(ParserTest, MultipleStatements)
{
  auto parser = tcalc::ast::Parser{};

  auto res = parser.parse(
    "import something def func(x, y) x + y; let x = 1; let y = 2; func(x, y)");
  EXPECT_TRUE(res.has_value());
}

}
