// FILE: u1149_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1149, TC1_CallsTarget) {
  int num_rows{};
  int num_cols{};
  int initial_max_num_nonzeros{};
  ceres::internal::DynamicCompressedRowSparseMatrix object{};
  (void)object;
}
