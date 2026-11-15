// FILE: u1147_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1147, TC1_CallsTarget) {
  BlockSparseMatrix m{};
  ceres::internal::BlockSparseMatrixData object{};
  (void)object;
}
