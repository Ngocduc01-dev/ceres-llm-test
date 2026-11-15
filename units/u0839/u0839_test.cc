// FILE: u0839_test.cc
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ToCRSMatrixTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  object.ToCRSMatrix(nullptr);
}

