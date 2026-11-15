// FILE: u1208_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(CreateBlockDiagonalMatrixTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  std::vector<Block> & blocks a1{};
  object.CreateBlockDiagonalMatrix(a0, a1);
}

// P2: START -> 1 -> END
TEST(CreateBlockDiagonalMatrixTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  std::vector<Block> & blocks a1{};
  object.CreateBlockDiagonalMatrix(a0, a1);
}

// P3: START -> 1 -> END
TEST(CreateBlockDiagonalMatrixTest, TC3_CallsTarget) {
  CompressedRowSparseMatrix object{};
  double a0[5] = {};
  std::vector<Block> & blocks a1{};
  object.CreateBlockDiagonalMatrix(a0, a1);
}

