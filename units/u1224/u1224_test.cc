// FILE: u1224_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/block_sparse_matrix.cc"

// P1: START -> 1 -> END
TEST(SetBlockStructureOfCompressedRowSparseMatrixTest, TC1_CallsTarget) {
  SetBlockStructureOfCompressedRowSparseMatrix(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(SetBlockStructureOfCompressedRowSparseMatrixTest, TC2_CallsTarget) {
  SetBlockStructureOfCompressedRowSparseMatrix(nullptr, nullptr);
}

