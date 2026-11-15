// FILE: u1159_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1159, TC1_CallsTarget) {
  const ResidualBlockId residual_block{};
  ceres::internal::ProblemImpl object{};
  object.GetLossFunctionForResidualBlock(residual_block);
}
