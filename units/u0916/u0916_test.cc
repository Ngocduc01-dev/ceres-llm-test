// FILE: u0916_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ToDenseMatrixTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

// P2: START -> 1 -> END
TEST(ToDenseMatrixTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

