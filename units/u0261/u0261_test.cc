// FILE: u0261_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

TEST(Unit_u0261, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::internal::CompressedRowSparseMatrix object(1, 1, 1);
  object.mutable_cols();
}
