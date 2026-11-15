// FILE: u1527_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1527, TC1_CallsTarget) {
  ResidualBlockId residual_block{};
  ceres::Problem object{};
  object.RemoveResidualBlock(residual_block);
}
