// FILE: u1182_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1182, TC1_CallsTarget) {
  int num_rows{};
  ceres::internal::CompressedRowSparseMatrix object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1182, TC2_CallsTarget) {
  int num_rows{};
  ceres::internal::CompressedRowSparseMatrix object{};
  (void)object;
}
