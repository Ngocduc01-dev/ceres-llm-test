// FILE: u0838_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(SetZeroTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  object.SetZero();
}

