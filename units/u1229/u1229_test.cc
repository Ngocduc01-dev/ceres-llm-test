// FILE: u1229_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"
#include "ceres/casts.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END
TEST(SolveReducedLinearSystemTest, TC1_CallsTarget) {
  DenseSchurComplementSolver object{};
  LinearSolver::PerSolveOptions & a0{};
  double a1[5] = {};
  object.SolveReducedLinearSystem(a0, a1);
}

// P2: START -> 1 -> END
TEST(SolveReducedLinearSystemTest, TC2_CallsTarget) {
  DenseSchurComplementSolver object{};
  LinearSolver::PerSolveOptions & a0{};
  double a1[5] = {};
  object.SolveReducedLinearSystem(a0, a1);
}

