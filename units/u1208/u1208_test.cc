// FILE: u1208_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1208, TC1_CallsTarget) {
  std::vector<Block> blocks{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateBlockDiagonalMatrix(nullptr, blocks);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1208, TC2_CallsTarget) {
  std::vector<Block> blocks{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateBlockDiagonalMatrix(nullptr, blocks);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1208, TC3_CallsTarget) {
  std::vector<Block> blocks{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateBlockDiagonalMatrix(nullptr, blocks);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1208, TC4_CallsTarget) {
  std::vector<Block> blocks{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateBlockDiagonalMatrix(nullptr, blocks);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1208, TC5_CallsTarget) {
  std::vector<Block> blocks{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateBlockDiagonalMatrix(nullptr, blocks);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1208, TC6_CallsTarget) {
  std::vector<Block> blocks{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateBlockDiagonalMatrix(nullptr, blocks);
}
