// FILE: u1415_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(u1415_Test, TC1_CallsTarget) {
  OptionsAreValidForSparseSchur(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1415_Test, TC2_CallsTarget) {
  OptionsAreValidForSparseSchur(nullptr, nullptr);
}
