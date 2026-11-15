// FILE: u1500_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1500_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.RemoveResidualBlock(nullptr);
}

// P2: START -> 1 -> END
TEST(u1500_Test, TC2_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.RemoveResidualBlock(nullptr);
}
