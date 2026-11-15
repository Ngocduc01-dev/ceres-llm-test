// FILE: u1501_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1501_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.CreateReducedProgram(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1501_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.CreateReducedProgram(nullptr, nullptr, nullptr);
}
