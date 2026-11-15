// FILE: u0933_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0933, TC1_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0933, TC2_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0933, TC3_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}
