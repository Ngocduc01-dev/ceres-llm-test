// FILE: u1001_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_evaluator.h"

// P1: START -> 1 -> END
TEST(NumEffectiveParametersTest, TC1_CallsTarget) {
  GradientProblemEvaluator object{};
  object.NumEffectiveParameters();
}

