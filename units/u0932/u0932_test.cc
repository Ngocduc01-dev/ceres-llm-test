// FILE: u0932_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ToDenseMatrixTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

// P2: START -> 1 -> END
TEST(ToDenseMatrixTest, TC2_CallsTarget) {
  BlockSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

// P3: START -> 1 -> END
TEST(ToDenseMatrixTest, TC3_CallsTarget) {
  BlockSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

