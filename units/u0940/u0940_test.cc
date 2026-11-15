// FILE: u0940_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0940, TC1_CallsTarget) {
  int new_max_num_nonzeros{};
  ceres::internal::TripletSparseMatrix object{};
  object.Reserve(new_max_num_nonzeros);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0940, TC2_CallsTarget) {
  int new_max_num_nonzeros{};
  ceres::internal::TripletSparseMatrix object{};
  object.Reserve(new_max_num_nonzeros);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0940, TC3_CallsTarget) {
  int new_max_num_nonzeros{};
  ceres::internal::TripletSparseMatrix object{};
  object.Reserve(new_max_num_nonzeros);
}
