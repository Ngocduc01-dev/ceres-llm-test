// FILE: u1000_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_evaluator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1000, TC1_CallsTarget) {
  ceres::internal::GradientProblemEvaluator object{};
  object.NumParameters();
}
