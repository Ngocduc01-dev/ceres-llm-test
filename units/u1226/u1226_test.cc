// FILE: u1226_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1226, TC1_CallsTarget) {
  int start_col_block{};
  int end_col_block{};
  ceres::internal::PartitionedMatrixView object{};
  object.CreateBlockDiagonalMatrixLayout(start_col_block, end_col_block);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1226, TC2_CallsTarget) {
  int start_col_block{};
  int end_col_block{};
  ceres::internal::PartitionedMatrixView object{};
  object.CreateBlockDiagonalMatrixLayout(start_col_block, end_col_block);
}
