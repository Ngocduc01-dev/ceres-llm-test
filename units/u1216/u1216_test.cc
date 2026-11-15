// FILE: u1216_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(SquaredColumnNormTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  object.SquaredColumnNorm(a0);
}

// P2: START -> 1 -> END
TEST(SquaredColumnNormTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  object.SquaredColumnNorm(a0);
}

// P3: START -> 1 -> END
TEST(SquaredColumnNormTest, TC3_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  object.SquaredColumnNorm(a0);
}

