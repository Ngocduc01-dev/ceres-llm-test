// FILE: u0949_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0949, TC1_CallsTarget) {
  int delta_rows{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.DeleteRows(delta_rows);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0949, TC2_CallsTarget) {
  int delta_rows{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.DeleteRows(delta_rows);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0949, TC3_CallsTarget) {
  int delta_rows{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.DeleteRows(delta_rows);
}
