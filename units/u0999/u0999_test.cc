// FILE: u0999_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_evaluator.h"

// P1: START -> 1 -> END
TEST(PlusTest, TC1_CallsTarget) {
  GradientProblemEvaluator object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Plus(a0, a1, a2);
}

