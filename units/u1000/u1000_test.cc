// FILE: u1000_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_evaluator.h"

// P1: START -> 1 -> END
TEST(NumParametersTest, TC1_CallsTarget) {
  GradientProblemEvaluator object{};
  object.NumParameters();
}

