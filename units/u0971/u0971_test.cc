// FILE: u0971_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(CopyDataTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix & orig a0{};
  object.CopyData(a0);
}

// P2: START -> 1 -> END
TEST(CopyDataTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix & orig a0{};
  object.CopyData(a0);
}

