// FILE: u0933_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ToDenseMatrixTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

// P2: START -> 1 -> END
TEST(ToDenseMatrixTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

// P3: START -> 1 -> END
TEST(ToDenseMatrixTest, TC3_CallsTarget) {
  CompressedRowSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

