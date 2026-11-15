// FILE: u0947_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0947, TC1_CallsTarget) {
  ceres::internal::TripletSparseMatrix object{};
  object.AllTripletsWithinBounds();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0947, TC2_CallsTarget) {
  ceres::internal::TripletSparseMatrix object{};
  object.AllTripletsWithinBounds();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0947, TC3_CallsTarget) {
  ceres::internal::TripletSparseMatrix object{};
  object.AllTripletsWithinBounds();
}
