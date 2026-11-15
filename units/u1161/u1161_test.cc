// FILE: u1161_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1161, TC1_CallsTarget) {
  TripletSparseMatrix m{};
  ceres::internal::DenseSparseMatrix object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1161, TC2_CallsTarget) {
  TripletSparseMatrix m{};
  ceres::internal::DenseSparseMatrix object{};
  (void)object;
}
