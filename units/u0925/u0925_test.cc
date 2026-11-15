// FILE: u0925_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(SquaredColumnNormTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  double a0[5] = {};
  object.SquaredColumnNorm(a0);
}

// P2: START -> 1 -> END
TEST(SquaredColumnNormTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  double a0[5] = {};
  object.SquaredColumnNorm(a0);
}

