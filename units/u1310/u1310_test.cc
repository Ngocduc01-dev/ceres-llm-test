// FILE: u1310_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(u1310_Test, TC1_CallsTarget) {
  OptionsAreValidForDenseSolver(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1310_Test, TC2_CallsTarget) {
  OptionsAreValidForDenseSolver(nullptr, nullptr);
}
