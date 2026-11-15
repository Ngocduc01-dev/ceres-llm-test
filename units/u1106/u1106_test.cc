// FILE: u1106_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ClearRowsTest, TC1_CallsTarget) {
  DynamicCompressedRowSparseMatrix object{};
  int a0 = 0;
  int a1 = 0;
  object.ClearRows(a0, a1);
}

// P2: START -> 1 -> END
TEST(ClearRowsTest, TC2_CallsTarget) {
  DynamicCompressedRowSparseMatrix object{};
  int a0 = 0;
  int a1 = 0;
  object.ClearRows(a0, a1);
}

