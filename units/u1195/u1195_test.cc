// FILE: u1195_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(LinearSolverForZeroEBlocksTest, TC1_CallsTarget) {
  LinearSolver object{};
  LinearSolverType a0{};
  object.LinearSolverForZeroEBlocks(a0);
}

// P2: START -> 1 -> END
TEST(LinearSolverForZeroEBlocksTest, TC2_CallsTarget) {
  LinearSolver object{};
  LinearSolverType a0{};
  object.LinearSolverForZeroEBlocks(a0);
}

// P3: START -> 1 -> END
TEST(LinearSolverForZeroEBlocksTest, TC3_CallsTarget) {
  LinearSolver object{};
  LinearSolverType a0{};
  object.LinearSolverForZeroEBlocks(a0);
}

