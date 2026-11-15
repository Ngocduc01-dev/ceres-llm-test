// FILE: u0773_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_col_sparse_matrix_utils.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(CompressedColumnScalarMatrixToBlockMatrixTest, TC1_CallsTarget) {
  int a0[5] = {};
  int a1[5] = {};
  std::vector<Block> & row_blocks a2{};
  std::vector<Block> & col_blocks a3{};
  int a4[5] = {};
  int a5[5] = {};
  ceres::internal::CompressedColumnScalarMatrixToBlockMatrix(a0, a1, a2, a3, a4, a5);
}

// P2: START -> 1 -> END
TEST(CompressedColumnScalarMatrixToBlockMatrixTest, TC2_CallsTarget) {
  int a0[5] = {};
  int a1[5] = {};
  std::vector<Block> & row_blocks a2{};
  std::vector<Block> & col_blocks a3{};
  int a4[5] = {};
  int a5[5] = {};
  ceres::internal::CompressedColumnScalarMatrixToBlockMatrix(a0, a1, a2, a3, a4, a5);
}

// P3: START -> 1 -> END
TEST(CompressedColumnScalarMatrixToBlockMatrixTest, TC3_CallsTarget) {
  int a0[5] = {};
  int a1[5] = {};
  std::vector<Block> & row_blocks a2{};
  std::vector<Block> & col_blocks a3{};
  int a4[5] = {};
  int a5[5] = {};
  ceres::internal::CompressedColumnScalarMatrixToBlockMatrix(a0, a1, a2, a3, a4, a5);
}

