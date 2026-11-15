// FILE: u0971_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0971, TC1_CallsTarget) {
  TripletSparseMatrix orig{};
  ceres::internal::TripletSparseMatrix object{};
  object.CopyData(orig);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0971, TC2_CallsTarget) {
  TripletSparseMatrix orig{};
  ceres::internal::TripletSparseMatrix object{};
  object.CopyData(orig);
}
