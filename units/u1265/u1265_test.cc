// FILE: u1265_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1265_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.MaxDerivativesPerResidualBlock();
}

// P2: START -> 1 -> END
TEST(u1265_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.MaxDerivativesPerResidualBlock();
}

// P3: START -> 1 -> END
TEST(u1265_Test, TC3_CallsTarget) {
  ceres::internal::Program target{};
  target.MaxDerivativesPerResidualBlock();
}
