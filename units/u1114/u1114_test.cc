// FILE: u1114_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1114, TC1_CallsTarget) {
  int row{};
  int col{};
  double value{};
  ceres::internal::DynamicCompressedRowSparseMatrix object{};
  object.InsertEntry(row, col, value);
}
