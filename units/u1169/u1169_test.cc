// FILE: u1169_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  int a3 = 0;
  object.RightMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

// P2: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  int a3 = 0;
  object.RightMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

