// FILE: u1074_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  DenseSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  object.RightMultiplyAndAccumulate(a0, a1);
}

