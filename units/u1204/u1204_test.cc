// FILE: u1204_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  int a3 = 0;
  object.LeftMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

// P2: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateTest, TC2_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  int a3 = 0;
  object.LeftMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

// P3: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateTest, TC3_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  int a3 = 0;
  object.LeftMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

