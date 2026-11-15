// FILE: u1481_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluation_callback.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1481_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1481_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1481_Test, TC3_CallsTarget) {
  ceres::internal::Program target{};
  target.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1481_Test, TC4_CallsTarget) {
  ceres::internal::Program target{};
  target.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}
