// FILE: u1194_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(TransposeTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  object.Transpose();
}

// P2: START -> 1 -> END
TEST(TransposeTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  object.Transpose();
}

