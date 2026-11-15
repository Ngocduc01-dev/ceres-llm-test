// FILE: u1150_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1150, TC1_CallsTarget) {
  BlockSparseMatrix m{};
  CompressedRowSparseMatrix::StorageType product_storage_type{};
  ceres::internal::InnerProductComputer object{};
  object.Create(m, product_storage_type);
}
