// FILE: u1191_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END
TEST(ScaleColumnsTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  int a2 = 0;
  object.ScaleColumns(a0, nullptr, a2);
}

// P2: START -> 1 -> END
TEST(ScaleColumnsTest, TC2_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  int a2 = 0;
  object.ScaleColumns(a0, nullptr, a2);
}

