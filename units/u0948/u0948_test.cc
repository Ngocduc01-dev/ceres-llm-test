// FILE: u0948_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(CreateFromTextFileTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  object.CreateFromTextFile(nullptr);
}

// P2: START -> 1 -> END
TEST(CreateFromTextFileTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  object.CreateFromTextFile(nullptr);
}

