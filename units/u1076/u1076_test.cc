// FILE: u1076_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ScaleColumnsTest, TC1_CallsTarget) {
  DenseSparseMatrix object{};
  double a0[5] = {};
  object.ScaleColumns(a0);
}

