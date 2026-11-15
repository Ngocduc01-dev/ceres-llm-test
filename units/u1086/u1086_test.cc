// FILE: u1086_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_random_access_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1086, TC1_CallsTarget) {
  int row_block_id{};
  int col_block_id{};
  ceres::internal::BlockRandomAccessSparseMatrix object{};
  object.GetCell(row_block_id, col_block_id, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1086, TC2_CallsTarget) {
  int row_block_id{};
  int col_block_id{};
  ceres::internal::BlockRandomAccessSparseMatrix object{};
  object.GetCell(row_block_id, col_block_id, nullptr, nullptr, nullptr, nullptr);
}
