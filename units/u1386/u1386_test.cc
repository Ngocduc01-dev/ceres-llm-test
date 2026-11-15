// FILE: u1386_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1386_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.ToString();
}

// P2: START -> 1 -> END
TEST(u1386_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.ToString();
}
