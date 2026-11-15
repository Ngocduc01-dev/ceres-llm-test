// FILE: u1168_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(CreateSparseDiagonalMatrixTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  double a0[5] = {};
  int a1 = 0;
  object.CreateSparseDiagonalMatrix(a0, a1);
}

// P2: START -> 1 -> END
TEST(CreateSparseDiagonalMatrixTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  double a0[5] = {};
  int a1 = 0;
  object.CreateSparseDiagonalMatrix(a0, a1);
}

