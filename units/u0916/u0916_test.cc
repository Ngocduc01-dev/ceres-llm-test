// FILE: u0916_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0916, TC1_CallsTarget) {
  ceres::internal::TripletSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0916, TC2_CallsTarget) {
  ceres::internal::TripletSparseMatrix object{};
  object.ToDenseMatrix(nullptr);
}
