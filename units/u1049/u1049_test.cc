// FILE: u1049_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"

// P1: START -> 1 -> END
TEST(EvaluateTest, TC1_CallsTarget) {
  GradientProblem object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(EvaluateTest, TC2_CallsTarget) {
  GradientProblem object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

