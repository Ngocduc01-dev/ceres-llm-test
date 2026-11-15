// FILE: u1167_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(operator=Test, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix & rhs a0{};
  object.operator=(a0);
}

// P2: START -> 1 -> END
TEST(operator=Test, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix & rhs a0{};
  object.operator=(a0);
}

