// FILE: u1167_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1167, TC1_CallsTarget) {
  TripletSparseMatrix rhs{};
  ceres::internal::TripletSparseMatrix object{};
  object(rhs);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1167, TC2_CallsTarget) {
  TripletSparseMatrix rhs{};
  ceres::internal::TripletSparseMatrix object{};
  object(rhs);
}
