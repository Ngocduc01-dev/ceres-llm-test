// FILE: u1122_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END
TEST(EvaluateTest, TC1_CallsTarget) {
  LineSearchFunction object{};
  double a0 = 0.0;
  bool a1 = false;
  object.Evaluate(a0, a1, nullptr);
}

// P2: START -> 1 -> END
TEST(EvaluateTest, TC2_CallsTarget) {
  LineSearchFunction object{};
  double a0 = 0.0;
  bool a1 = false;
  object.Evaluate(a0, a1, nullptr);
}

// P3: START -> 1 -> END
TEST(EvaluateTest, TC3_CallsTarget) {
  LineSearchFunction object{};
  double a0 = 0.0;
  bool a1 = false;
  object.Evaluate(a0, a1, nullptr);
}

