// FILE: u0887_test.cc
#include "gtest/gtest.h"
#include "ceres/program_evaluator.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(CreateJacobianTest, TC1_CallsTarget) {
  ProgramEvaluator object{};
  object.CreateJacobian();
}

