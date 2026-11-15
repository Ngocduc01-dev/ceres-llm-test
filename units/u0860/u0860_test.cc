// FILE: u0860_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_evaluator.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0860, TC1_CallsTarget) {
  ceres::internal::GradientProblemEvaluator object{};
  object.CreateJacobian();
}
