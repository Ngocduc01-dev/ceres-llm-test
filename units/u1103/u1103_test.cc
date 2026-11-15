// FILE: u1103_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(SymmetricRightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  BlockRandomAccessSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  object.SymmetricRightMultiplyAndAccumulate(a0, a1);
}

// P2: START -> 1 -> END
TEST(SymmetricRightMultiplyAndAccumulateTest, TC2_CallsTarget) {
  BlockRandomAccessSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  object.SymmetricRightMultiplyAndAccumulate(a0, a1);
}

// P3: START -> 1 -> END
TEST(SymmetricRightMultiplyAndAccumulateTest, TC3_CallsTarget) {
  BlockRandomAccessSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  object.SymmetricRightMultiplyAndAccumulate(a0, a1);
}

