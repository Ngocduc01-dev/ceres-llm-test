// FILE: u1261_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1261_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.MaxParametersPerResidualBlock();
}

// P2: START -> 1 -> END
TEST(u1261_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.MaxParametersPerResidualBlock();
}
