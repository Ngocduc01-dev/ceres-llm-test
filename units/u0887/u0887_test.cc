// FILE: u0887_test.cc
#include "gtest/gtest.h"
#include "ceres/program_evaluator.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0887, TC1_CallsTarget) {
  ceres::internal::ProgramEvaluator object{};
  object.CreateJacobian();
}
