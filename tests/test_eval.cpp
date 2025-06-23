#include <cmath>
#include <gtest/gtest.h>
#include <limits>
#include <tcalc/eval.hpp>

namespace {

TEST(EvalTest, Expression)
{
  auto evaluator = tcalc::Evaluator{};

  auto res = evaluator.eval("1 + 2 * 3 / sqrt(pow(3, 2)) - pi");
  EXPECT_TRUE(res.has_value());
  EXPECT_TRUE(std::abs(*res - (3 - M_PI)) <
              std::numeric_limits<double>::epsilon());
}

TEST(EvalTest, FuncDefinition)
{
  auto evaluator = tcalc::Evaluator{};

  auto res = evaluator.eval_prog("def f(x) x + 1; f(1)");
  EXPECT_TRUE(res.has_value());

  const auto& values = res.value();
  EXPECT_EQ(values.size(), 2);

  EXPECT_TRUE(std::abs(values[1] - 2) < std::numeric_limits<double>::epsilon());
}

TEST(EvalTest, VarDefinition)
{
  auto evaluator = tcalc::Evaluator{};

  auto res = evaluator.eval_prog("let x = 1; x");
  EXPECT_TRUE(res.has_value());

  const auto& values = res.value();
  EXPECT_EQ(values.size(), 2);

  EXPECT_TRUE(std::abs(values[1] - 1) < std::numeric_limits<double>::epsilon());
}

TEST(EvalTest, IfStatement)
{
  auto evaluator = tcalc::Evaluator{};

  auto res = evaluator.eval("if 1 > 0 then 1 else 0");
  EXPECT_TRUE(res.has_value());
  EXPECT_TRUE(std::abs(*res - 1) < std::numeric_limits<double>::epsilon());
}

TEST(EvalTest, ImportStatement)
{
  auto evaluator = tcalc::Evaluator{};

  auto res = evaluator.eval("import doesnotexist");
  EXPECT_FALSE(res.has_value());

  const auto& err = res.error();
  EXPECT_EQ(err.code(), tcalc::error::Code::FILE_NOT_FOUND);
}

TEST(EvalTest, MultipleStatements)
{
  auto evaluator = tcalc::Evaluator{};

  auto res = evaluator.eval_prog(
    "def func(x, y) x + y; let x = 1; let y = 2; func(x, y)");
  EXPECT_TRUE(res.has_value());

  const auto& values = res.value();
  EXPECT_EQ(values.size(), 4);

  EXPECT_TRUE(std::abs(values[3] - 3) < std::numeric_limits<double>::epsilon());
}

}
