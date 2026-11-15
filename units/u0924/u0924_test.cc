// FILE: u0924_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0924, TC1_CallsTarget) {
  int num_nonzeros{};
  ceres::internal::TripletSparseMatrix object{};
  object.set_num_nonzeros(num_nonzeros);
}
