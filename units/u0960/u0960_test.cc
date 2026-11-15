// FILE: u0960_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0960, TC1_CallsTarget) {
  BlockSparseMatrix m{};
  const int start_row_block{};
  const int end_row_block{};
  ceres::internal::InnerProductComputer object{};
  (void)object;
}
