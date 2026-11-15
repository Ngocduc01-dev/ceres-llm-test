// FILE: u0254_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0254, PathP1) {
  ceres::internal::CompressedRowSparseMatrix object(1, 1, 1);
  object.num_cols();
}
