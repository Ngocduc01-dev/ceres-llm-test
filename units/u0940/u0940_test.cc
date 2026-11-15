// FILE: u0940_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ReserveTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  int a0 = 0;
  object.Reserve(a0);
}

// P2: START -> 1 -> END
TEST(ReserveTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  int a0 = 0;
  object.Reserve(a0);
}

// P3: START -> 1 -> END
TEST(ReserveTest, TC3_CallsTarget) {
  TripletSparseMatrix object{};
  int a0 = 0;
  object.Reserve(a0);
}

