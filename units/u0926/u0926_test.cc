// FILE: u0926_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ScaleColumnsTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  double a0[5] = {};
  object.ScaleColumns(a0);
}

// P2: START -> 1 -> END
TEST(ScaleColumnsTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  double a0[5] = {};
  object.ScaleColumns(a0);
}

