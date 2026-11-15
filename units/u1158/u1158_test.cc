// FILE: u1158_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1158, TC1_CallsTarget) {
  const ResidualBlockId residual_block{};
  ceres::internal::ProblemImpl object{};
  object.GetCostFunctionForResidualBlock(residual_block);
}
