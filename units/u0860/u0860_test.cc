// FILE: u0860_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_evaluator.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(CreateJacobianTest, TC1_CallsTarget) {
  GradientProblemEvaluator object{};
  object.CreateJacobian();
}

