// FILE: u0918_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ScaleColumnsTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  object.ScaleColumns(a0);
}

// P2: START -> 1 -> END
TEST(ScaleColumnsTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  object.ScaleColumns(a0);
}

