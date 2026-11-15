// FILE: u1480_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(u1480_Test, TC1_CallsTarget) {
  OptionsAreValidForLinearSolver(nullptr, nullptr);
}
