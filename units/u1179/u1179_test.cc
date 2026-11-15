// FILE: u1179_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1179, TC1_CallsTarget) {
  TripletSparseMatrix B{};
  ceres::internal::TripletSparseMatrix object{};
  object.AppendCols(B);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1179, TC2_CallsTarget) {
  TripletSparseMatrix B{};
  ceres::internal::TripletSparseMatrix object{};
  object.AppendCols(B);
}
