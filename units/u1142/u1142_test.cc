// FILE: u1142_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(LineSearchOptionsAreValidTest, TC1_CallsTarget) {
  Solver::Options & options a0{};
  LineSearchOptionsAreValid(a0, nullptr);
}

// P2: START -> 1 -> END
TEST(LineSearchOptionsAreValidTest, TC2_CallsTarget) {
  Solver::Options & options a0{};
  LineSearchOptionsAreValid(a0, nullptr);
}

// P3: START -> 1 -> END
TEST(LineSearchOptionsAreValidTest, TC3_CallsTarget) {
  Solver::Options & options a0{};
  LineSearchOptionsAreValid(a0, nullptr);
}

