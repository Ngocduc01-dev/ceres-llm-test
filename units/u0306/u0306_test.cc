// FILE: u0306_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_evaluator.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0306, PathP1) {
  ceres::internal::GradientProblemEvaluator target;
  target.NumResiduals();
}
