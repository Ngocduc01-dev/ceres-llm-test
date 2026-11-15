// FILE: u0801_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(IsIterativeSolverTest, TC1_CallsTarget) {
  LinearSolverType a0{};
  IsIterativeSolver(a0);
}

