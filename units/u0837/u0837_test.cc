// FILE: u0837_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0837, TC1_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix object{};
  object.~CompressedRowSparseMatrix();
}
