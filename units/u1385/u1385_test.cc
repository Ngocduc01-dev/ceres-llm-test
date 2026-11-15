// FILE: u1385_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1385_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.MaxScratchDoublesNeededForEvaluate();
}

// P2: START -> 1 -> END
TEST(u1385_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.MaxScratchDoublesNeededForEvaluate();
}
