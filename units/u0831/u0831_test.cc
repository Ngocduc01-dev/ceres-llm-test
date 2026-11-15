// FILE: u0831_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0831, TC1_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.transpose_block_structure();
}
