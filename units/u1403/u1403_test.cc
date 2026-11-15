// FILE: u1403_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1403_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.ParameterBlocksAreFinite(nullptr);
}

// P2: START -> 1 -> END
TEST(u1403_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.ParameterBlocksAreFinite(nullptr);
}

// P3: START -> 1 -> END
TEST(u1403_Test, TC3_CallsTarget) {
  ceres::internal::Program target{};
  target.ParameterBlocksAreFinite(nullptr);
}
