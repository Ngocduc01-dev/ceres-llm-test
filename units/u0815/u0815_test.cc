// FILE: u0815_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(CommonOptionsAreValidTest, TC1_CallsTarget) {
  Solver::Options & options a0{};
  CommonOptionsAreValid(a0, nullptr);
}

// P2: START -> 1 -> END
TEST(CommonOptionsAreValidTest, TC2_CallsTarget) {
  Solver::Options & options a0{};
  CommonOptionsAreValid(a0, nullptr);
}

// P3: START -> 1 -> END
TEST(CommonOptionsAreValidTest, TC3_CallsTarget) {
  Solver::Options & options a0{};
  CommonOptionsAreValid(a0, nullptr);
}

