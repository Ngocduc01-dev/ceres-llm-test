// FILE: u1319_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1319_Test, TC1_CallsTarget) {
  ceres::internal::BlockSparseMatrix target{};
  target.ToCompressedRowSparseMatrix();
}
