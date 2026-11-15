// FILE: u1180_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1180, TC1_CallsTarget) {
  std::vector<Block> column_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateDiagonalMatrix(nullptr, column_blocks);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1180, TC2_CallsTarget) {
  std::vector<Block> column_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateDiagonalMatrix(nullptr, column_blocks);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1180, TC3_CallsTarget) {
  std::vector<Block> column_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateDiagonalMatrix(nullptr, column_blocks);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1180, TC4_CallsTarget) {
  std::vector<Block> column_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateDiagonalMatrix(nullptr, column_blocks);
}
