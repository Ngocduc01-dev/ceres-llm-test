// FILE: u1114_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(InsertEntryTest, TC1_CallsTarget) {
  DynamicCompressedRowSparseMatrix object{};
  int a0 = 0;
  int a1 = 0;
  double a2 = 0.0;
  object.InsertEntry(a0, a1, a2);
}

