// FILE: u1072_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END
TEST(InvertTest, TC1_CallsTarget) {
  BlockRandomAccessDiagonalMatrix object{};
  object.Invert();
}

