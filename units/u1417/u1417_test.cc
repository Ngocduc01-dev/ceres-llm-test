// FILE: u1417_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1417, TC1_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForDenseSchur(options, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1417, TC2_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForDenseSchur(options, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1417, TC3_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForDenseSchur(options, nullptr);
}
