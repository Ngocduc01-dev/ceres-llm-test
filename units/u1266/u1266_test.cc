// FILE: u1266_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1266_Test, TC1_CallsTarget) {
  ceres::internal::ResidualBlock target{};
  target.NumScratchDoublesForEvaluate();
}

// P2: START -> 1 -> END
TEST(u1266_Test, TC2_CallsTarget) {
  ceres::internal::ResidualBlock target{};
  target.NumScratchDoublesForEvaluate();
}

// P3: START -> 1 -> END
TEST(u1266_Test, TC3_CallsTarget) {
  ceres::internal::ResidualBlock target{};
  target.NumScratchDoublesForEvaluate();
}
