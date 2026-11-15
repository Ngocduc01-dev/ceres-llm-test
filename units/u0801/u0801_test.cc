// FILE: u0801_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0801, TC1_CallsTarget) {
  LinearSolverType type{};
  ceres::IsIterativeSolver(type);
}
