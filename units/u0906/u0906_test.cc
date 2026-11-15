// FILE: u0906_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(SetMaxNumNonZerosTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  int a0 = 0;
  object.SetMaxNumNonZeros(a0);
}

