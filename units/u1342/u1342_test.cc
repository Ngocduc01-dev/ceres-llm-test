// FILE: u1342_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1342, TC1_CallsTarget) {
  const ResidualBlockId residual_block{};
  ceres::Problem object{};
  object.GetLossFunctionForResidualBlock(residual_block);
}
