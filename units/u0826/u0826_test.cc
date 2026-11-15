// FILE: u0826_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(mutable_matrixTest, TC1_CallsTarget) {
  BlockRandomAccessDiagonalMatrix object{};
  object.mutable_matrix();
}

