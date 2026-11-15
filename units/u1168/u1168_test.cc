// FILE: u1168_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1168, TC1_CallsTarget) {
  int num_rows{};
  ceres::internal::TripletSparseMatrix object{};
  object.CreateSparseDiagonalMatrix(nullptr, num_rows);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1168, TC2_CallsTarget) {
  int num_rows{};
  ceres::internal::TripletSparseMatrix object{};
  object.CreateSparseDiagonalMatrix(nullptr, num_rows);
}
