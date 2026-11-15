// FILE: u0912_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END
TEST(FactorAndSolveTest, TC1_CallsTarget) {
  SparseCholesky object{};
  double a1[5] = {};
  double a2[5] = {};
  object.FactorAndSolve(nullptr, a1, a2, nullptr);
}

// P2: START -> 1 -> END
TEST(FactorAndSolveTest, TC2_CallsTarget) {
  SparseCholesky object{};
  double a1[5] = {};
  double a2[5] = {};
  object.FactorAndSolve(nullptr, a1, a2, nullptr);
}

