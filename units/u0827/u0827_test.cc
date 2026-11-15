// FILE: u0827_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(matrixTest, TC1_CallsTarget) {
  BlockRandomAccessSparseMatrix object{};
  object.matrix();
}

