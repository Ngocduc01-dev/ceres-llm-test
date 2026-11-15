// FILE: u0967_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(AllocateValuesTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  int a0 = 0;
  object.AllocateValues(a0);
}

