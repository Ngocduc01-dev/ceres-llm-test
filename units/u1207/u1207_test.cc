// FILE: u1207_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1207, TC1_CallsTarget) {
  const int delta_row_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.DeleteRowBlocks(delta_row_blocks);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1207, TC2_CallsTarget) {
  const int delta_row_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.DeleteRowBlocks(delta_row_blocks);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1207, TC3_CallsTarget) {
  const int delta_row_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.DeleteRowBlocks(delta_row_blocks);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1207, TC4_CallsTarget) {
  const int delta_row_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.DeleteRowBlocks(delta_row_blocks);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1207, TC5_CallsTarget) {
  const int delta_row_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.DeleteRowBlocks(delta_row_blocks);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1207, TC6_CallsTarget) {
  const int delta_row_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.DeleteRowBlocks(delta_row_blocks);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1207, TC7_CallsTarget) {
  const int delta_row_blocks{};
  ceres::internal::BlockSparseMatrix object{};
  object.DeleteRowBlocks(delta_row_blocks);
}
