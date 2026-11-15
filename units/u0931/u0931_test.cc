// FILE: u0931_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ScaleColumnsTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  object.ScaleColumns(a0);
}

// P2: START -> 1 -> END
TEST(ScaleColumnsTest, TC2_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  object.ScaleColumns(a0);
}

// P3: START -> 1 -> END
TEST(ScaleColumnsTest, TC3_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  object.ScaleColumns(a0);
}

