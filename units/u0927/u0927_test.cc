// FILE: u0927_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ToTextFileTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  object.ToTextFile(nullptr);
}

// P2: START -> 1 -> END
TEST(ToTextFileTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  object.ToTextFile(nullptr);
}

