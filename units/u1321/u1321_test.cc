// FILE: u1321_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1321_Test, TC1_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix target{};
  target.FromTripletSparseMatrixTransposed(nullptr);
}
