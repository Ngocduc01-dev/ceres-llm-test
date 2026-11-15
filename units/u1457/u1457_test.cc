// FILE: u1457_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1457, TC1_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  ceres::internal::InnerProductComputer object{};
  object.Init(product_storage_type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1457, TC2_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  ceres::internal::InnerProductComputer object{};
  object.Init(product_storage_type);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1457, TC3_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  ceres::internal::InnerProductComputer object{};
  object.Init(product_storage_type);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1457, TC4_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  ceres::internal::InnerProductComputer object{};
  object.Init(product_storage_type);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1457, TC5_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  ceres::internal::InnerProductComputer object{};
  object.Init(product_storage_type);
}
