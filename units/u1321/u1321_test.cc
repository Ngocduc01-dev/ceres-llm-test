// FILE: u1321_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1321, TC1_CallsTarget) {
  TripletSparseMatrix input{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.FromTripletSparseMatrixTransposed(input);
}
