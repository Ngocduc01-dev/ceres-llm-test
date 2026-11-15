// FILE: u1024_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(IsValidTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  object.IsValid();
}

