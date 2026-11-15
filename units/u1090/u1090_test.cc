// FILE: u1090_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  BlockRandomAccessDiagonalMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  object.RightMultiplyAndAccumulate(a0, a1);
}

