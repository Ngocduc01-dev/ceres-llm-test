// FILE: u1119_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(FinalizeTest, TC1_CallsTarget) {
  DynamicCompressedRowSparseMatrix object{};
  int a0 = 0;
  object.Finalize(a0);
}

// P2: START -> 1 -> END
TEST(FinalizeTest, TC2_CallsTarget) {
  DynamicCompressedRowSparseMatrix object{};
  int a0 = 0;
  object.Finalize(a0);
}

// P3: START -> 1 -> END
TEST(FinalizeTest, TC3_CallsTarget) {
  DynamicCompressedRowSparseMatrix object{};
  int a0 = 0;
  object.Finalize(a0);
}

