// FILE: u1130_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_autodiff_cost_function.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END
TEST(EvaluateTest, TC1_CallsTarget) {
  DynamicAutoDiffCostFunction object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(EvaluateTest, TC2_CallsTarget) {
  DynamicAutoDiffCostFunction object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

// P3: START -> 1 -> END
TEST(EvaluateTest, TC3_CallsTarget) {
  DynamicAutoDiffCostFunction object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

