// FILE: u1271_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1271_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.IsBoundsConstrained();
}

// P2: START -> 1 -> END
TEST(u1271_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.IsBoundsConstrained();
}

// P3: START -> 1 -> END
TEST(u1271_Test, TC3_CallsTarget) {
  ceres::internal::Program target{};
  target.IsBoundsConstrained();
}

// P4: START -> 1 -> END
TEST(u1271_Test, TC4_CallsTarget) {
  ceres::internal::Program target{};
  target.IsBoundsConstrained();
}
