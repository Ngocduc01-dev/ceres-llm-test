// FILE: u0949_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(DeleteRowsTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  int a0 = 0;
  object.DeleteRows(a0);
}

// P2: START -> 1 -> END
TEST(DeleteRowsTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  int a0 = 0;
  object.DeleteRows(a0);
}

// P3: START -> 1 -> END
TEST(DeleteRowsTest, TC3_CallsTarget) {
  CompressedRowSparseMatrix object{};
  int a0 = 0;
  object.DeleteRows(a0);
}

