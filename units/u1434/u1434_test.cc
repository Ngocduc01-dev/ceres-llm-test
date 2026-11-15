// FILE: u1434_test.cc
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1434, TC1_CallsTarget) {
  ceres::internal::TripletSparseMatrix object{};
  object.ToCRSMatrix(nullptr);
}
