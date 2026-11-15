// FILE: u1215_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  object.RightMultiplyAndAccumulate(a0, a1);
}

// P2: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  object.RightMultiplyAndAccumulate(a0, a1);
}

// P3: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC3_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  object.RightMultiplyAndAccumulate(a0, a1);
}

