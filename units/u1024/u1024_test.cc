// FILE: u1024_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1024, TC1_CallsTarget) {
  ceres::internal::TripletSparseMatrix object{};
  object.IsValid();
}
