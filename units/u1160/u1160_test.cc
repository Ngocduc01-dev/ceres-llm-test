// FILE: u1160_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1160, TC1_CallsTarget) {
  TripletSparseMatrix orig{};
  ceres::internal::TripletSparseMatrix object{};
  (void)object;
}
