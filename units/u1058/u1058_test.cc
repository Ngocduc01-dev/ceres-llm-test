// FILE: u1058_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"
#include "ceres/internal/numeric_diff.h"

// P1: START -> 1 -> END
TEST(EvaluateTest, TC1_CallsTarget) {
  DynamicNumericDiffCostFunction object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(EvaluateTest, TC2_CallsTarget) {
  DynamicNumericDiffCostFunction object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

// P3: START -> 1 -> END
TEST(EvaluateTest, TC3_CallsTarget) {
  DynamicNumericDiffCostFunction object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

