// FILE: u1318_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1318, TC1_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.ToCompressedRowSparseMatrixTranspose();
}
