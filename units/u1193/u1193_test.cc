// FILE: u1193_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(UpdateCompressedRowSparseMatrixTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  object.UpdateCompressedRowSparseMatrix(nullptr);
}

