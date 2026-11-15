// FILE: u1288_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1288_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.GetParameterBlocksForResidualBlock(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1288_Test, TC2_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.GetParameterBlocksForResidualBlock(nullptr, nullptr);
}
