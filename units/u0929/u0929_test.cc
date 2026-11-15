// FILE: u0929_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  int a3 = 0;
  object.RightMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

