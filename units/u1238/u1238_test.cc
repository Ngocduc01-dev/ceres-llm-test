// FILE: u1238_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/manifold.h"
#include "ceres/gradient_checker.cc"

// P1: START -> 1 -> END
TEST(EvaluateCostFunctionTest, TC1_CallsTarget) {
  double a1[5] = {};
  EvaluateCostFunction(nullptr, a1, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(EvaluateCostFunctionTest, TC2_CallsTarget) {
  double a1[5] = {};
  EvaluateCostFunction(nullptr, a1, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(EvaluateCostFunctionTest, TC3_CallsTarget) {
  double a1[5] = {};
  EvaluateCostFunction(nullptr, a1, nullptr, nullptr, nullptr, nullptr);
}

