// FILE: u1106_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1106, TC1_CallsTarget) {
  int row_start{};
  int num_rows{};
  ceres::internal::DynamicCompressedRowSparseMatrix object{};
  object.ClearRows(row_start, num_rows);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1106, TC2_CallsTarget) {
  int row_start{};
  int num_rows{};
  ceres::internal::DynamicCompressedRowSparseMatrix object{};
  object.ClearRows(row_start, num_rows);
}
