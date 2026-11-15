// FILE: u1119_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1119, TC1_CallsTarget) {
  int num_additional_elements{};
  ceres::internal::DynamicCompressedRowSparseMatrix object{};
  object.Finalize(num_additional_elements);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1119, TC2_CallsTarget) {
  int num_additional_elements{};
  ceres::internal::DynamicCompressedRowSparseMatrix object{};
  object.Finalize(num_additional_elements);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1119, TC3_CallsTarget) {
  int num_additional_elements{};
  ceres::internal::DynamicCompressedRowSparseMatrix object{};
  object.Finalize(num_additional_elements);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1119, TC4_CallsTarget) {
  int num_additional_elements{};
  ceres::internal::DynamicCompressedRowSparseMatrix object{};
  object.Finalize(num_additional_elements);
}
