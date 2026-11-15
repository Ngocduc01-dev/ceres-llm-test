// FILE: u1188_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1188, TC1_CallsTarget) {
  int num_rows{};
  int num_cols{};
  int max_num_nonzeros{};
  ceres::internal::TripletSparseMatrix object{};
  (void)object;
}
