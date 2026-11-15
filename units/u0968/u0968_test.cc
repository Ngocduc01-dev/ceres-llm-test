// FILE: u0968_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(FreeValuesTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  object.FreeValues(a0);
}

