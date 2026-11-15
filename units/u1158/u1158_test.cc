// FILE: u1158_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(GetCostFunctionForResidualBlockTest, TC1_CallsTarget) {
  ProblemImpl object{};
  ResidualBlockId a0{};
  object.GetCostFunctionForResidualBlock(a0);
}

