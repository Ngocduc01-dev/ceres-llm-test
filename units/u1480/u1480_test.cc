// FILE: u1480_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1480, TC1_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForLinearSolver(options, nullptr);
}
