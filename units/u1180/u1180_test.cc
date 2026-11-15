// FILE: u1180_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(CreateDiagonalMatrixTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  std::vector<Block> & column_blocks a1{};
  object.CreateDiagonalMatrix(a0, a1);
}

// P2: START -> 1 -> END
TEST(CreateDiagonalMatrixTest, TC2_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  std::vector<Block> & column_blocks a1{};
  object.CreateDiagonalMatrix(a0, a1);
}

// P3: START -> 1 -> END
TEST(CreateDiagonalMatrixTest, TC3_CallsTarget) {
  BlockSparseMatrix object{};
  double a0[5] = {};
  std::vector<Block> & column_blocks a1{};
  object.CreateDiagonalMatrix(a0, a1);
}

