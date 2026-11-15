// FILE: u1214_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(AppendRowsTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  CompressedRowSparseMatrix & m a0{};
  object.AppendRows(a0);
}

// P2: START -> 1 -> END
TEST(AppendRowsTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  CompressedRowSparseMatrix & m a0{};
  object.AppendRows(a0);
}

// P3: START -> 1 -> END
TEST(AppendRowsTest, TC3_CallsTarget) {
  CompressedRowSparseMatrix object{};
  CompressedRowSparseMatrix & m a0{};
  object.AppendRows(a0);
}

