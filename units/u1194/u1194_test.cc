// FILE: u1194_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1194, TC1_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix object{};
  object.Transpose();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1194, TC2_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix object{};
  object.Transpose();
}
