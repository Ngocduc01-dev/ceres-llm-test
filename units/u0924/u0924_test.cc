// FILE: u0924_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(set_num_nonzerosTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  int a0 = 0;
  object.set_num_nonzeros(a0);
}

