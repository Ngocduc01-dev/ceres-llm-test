// FILE: u1387_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1387_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.StateVectorToParameterBlocks(nullptr);
}

// P2: START -> 1 -> END
TEST(u1387_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.StateVectorToParameterBlocks(nullptr);
}

// P3: START -> 1 -> END
TEST(u1387_Test, TC3_CallsTarget) {
  ceres::internal::Program target{};
  target.StateVectorToParameterBlocks(nullptr);
}
