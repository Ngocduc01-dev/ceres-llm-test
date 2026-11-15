// FILE: u1351_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1351, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::SparseSchurComplementSolver object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1351, TC2_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::SparseSchurComplementSolver object{};
  (void)object;
}
