// FILE: u0906_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0906, TC1_CallsTarget) {
  int num_nonzeros{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.SetMaxNumNonZeros(num_nonzeros);
}
