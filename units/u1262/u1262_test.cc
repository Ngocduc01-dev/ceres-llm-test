// FILE: u1262_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1262_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.MaxResidualsPerResidualBlock();
}

// P2: START -> 1 -> END
TEST(u1262_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.MaxResidualsPerResidualBlock();
}
