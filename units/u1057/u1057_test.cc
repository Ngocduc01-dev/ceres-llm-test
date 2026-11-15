// FILE: u1057_test.cc
#include "gtest/gtest.h"
#include "ceres/conditioned_cost_function.h"
#include "ceres/cost_function.h"

// P1: START -> 1 -> END
TEST(EvaluateTest, TC1_CallsTarget) {
  ConditionedCostFunction object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(EvaluateTest, TC2_CallsTarget) {
  ConditionedCostFunction object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

// P3: START -> 1 -> END
TEST(EvaluateTest, TC3_CallsTarget) {
  ConditionedCostFunction object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

