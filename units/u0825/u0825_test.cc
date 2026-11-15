// FILE: u0825_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0825, TC1_CallsTarget) {
  ceres::internal::BlockRandomAccessDiagonalMatrix object{};
  object.matrix();
}
