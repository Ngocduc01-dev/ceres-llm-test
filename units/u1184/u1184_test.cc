// FILE: u1184_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1184, TC1_CallsTarget) {
  BlockSparseMatrix m{};
  const int start_row_block{};
  const int end_row_block{};
  CompressedRowSparseMatrix::StorageType product_storage_type{};
  ceres::internal::InnerProductComputer object{};
  object.Create(m, start_row_block, end_row_block, product_storage_type);
}
