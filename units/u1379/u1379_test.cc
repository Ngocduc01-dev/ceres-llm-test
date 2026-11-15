// FILE: u1379_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1379, TC1_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1379, TC2_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1379, TC3_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1379, TC4_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1379, TC5_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1379, TC6_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1379, TC7_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1379, TC8_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1379, TC9_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1379, TC10_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1379, TC11_CallsTarget) {
  const CompressedRowSparseMatrix::StorageType product_storage_type{};
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}
