// FILE: u1162_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(RefineTest, TC1_CallsTarget) {
  SparseIterativeRefiner object{};
  SparseMatrix & lhs a0{};
  double a1[5] = {};
  double a3[5] = {};
  object.Refine(a0, a1, nullptr, a3);
}

// P2: START -> 1 -> END
TEST(RefineTest, TC2_CallsTarget) {
  SparseIterativeRefiner object{};
  SparseMatrix & lhs a0{};
  double a1[5] = {};
  double a3[5] = {};
  object.Refine(a0, a1, nullptr, a3);
}

