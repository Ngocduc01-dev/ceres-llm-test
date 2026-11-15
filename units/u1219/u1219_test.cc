// FILE: u1219_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1219, TC1_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType storage_type{};
  const int num_nonzeros{};
  ceres::internal::InnerProductComputer object{};
  object.CreateResultMatrix(storage_type, num_nonzeros);
}
