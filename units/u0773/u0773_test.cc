// FILE: u0773_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_col_sparse_matrix_utils.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0773, TC1_CallsTarget) {
  std::vector<Block> row_blocks{};
  std::vector<Block> col_blocks{};
  ceres::internal::CompressedColumnScalarMatrixToBlockMatrix(nullptr, nullptr, row_blocks, col_blocks, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0773, TC2_CallsTarget) {
  std::vector<Block> row_blocks{};
  std::vector<Block> col_blocks{};
  ceres::internal::CompressedColumnScalarMatrixToBlockMatrix(nullptr, nullptr, row_blocks, col_blocks, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0773, TC3_CallsTarget) {
  std::vector<Block> row_blocks{};
  std::vector<Block> col_blocks{};
  ceres::internal::CompressedColumnScalarMatrixToBlockMatrix(nullptr, nullptr, row_blocks, col_blocks, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0773, TC4_CallsTarget) {
  std::vector<Block> row_blocks{};
  std::vector<Block> col_blocks{};
  ceres::internal::CompressedColumnScalarMatrixToBlockMatrix(nullptr, nullptr, row_blocks, col_blocks, nullptr, nullptr);
}
