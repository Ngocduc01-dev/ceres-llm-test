// FILE: u1431_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1431, TC1_CallsTarget) {
  const ResidualBlockId residual_block{};
  ceres::Problem object{};
  object.GetParameterBlocksForResidualBlock(residual_block, nullptr);
}
