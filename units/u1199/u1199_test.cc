// FILE: u1199_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ToTripletSparseMatrixTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  object.ToTripletSparseMatrix(nullptr);
}

// P2: START -> 1 -> END
TEST(ToTripletSparseMatrixTest, TC2_CallsTarget) {
  BlockSparseMatrix object{};
  object.ToTripletSparseMatrix(nullptr);
}

// P3: START -> 1 -> END
TEST(ToTripletSparseMatrixTest, TC3_CallsTarget) {
  BlockSparseMatrix object{};
  object.ToTripletSparseMatrix(nullptr);
}

