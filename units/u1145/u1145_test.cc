// FILE: u1145_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END
TEST(SetZeroTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  int a1 = 0;
  object.SetZero(nullptr, a1);
}

