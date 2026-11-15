// FILE: u1415_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1415, TC1_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForSparseSchur(options, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1415, TC2_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForSparseSchur(options, nullptr);
}
