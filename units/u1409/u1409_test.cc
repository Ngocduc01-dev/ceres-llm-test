// FILE: u1409_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1409_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.IsFeasible(nullptr);
}

// P2: START -> 1 -> END
TEST(u1409_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.IsFeasible(nullptr);
}

// P3: START -> 1 -> END
TEST(u1409_Test, TC3_CallsTarget) {
  ceres::internal::Program target{};
  target.IsFeasible(nullptr);
}

// P4: START -> 1 -> END
TEST(u1409_Test, TC4_CallsTarget) {
  ceres::internal::Program target{};
  target.IsFeasible(nullptr);
}
