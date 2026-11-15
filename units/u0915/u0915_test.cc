// FILE: u0915_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0915, TC1_CallsTarget) {
  ceres::internal::TripletSparseMatrix object{};
  object.LeftMultiplyAndAccumulate(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0915, TC2_CallsTarget) {
  ceres::internal::TripletSparseMatrix object{};
  object.LeftMultiplyAndAccumulate(nullptr, nullptr);
}
