// FILE: u1159_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(GetLossFunctionForResidualBlockTest, TC1_CallsTarget) {
  ProblemImpl object{};
  ResidualBlockId a0{};
  object.GetLossFunctionForResidualBlock(a0);
}

