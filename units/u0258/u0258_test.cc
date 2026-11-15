// FILE: u0258_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0258, PathP1) {
  ceres::internal::CompressedRowSparseMatrix object(1, 1, 1);
  object.set_num_rows(1);
}
