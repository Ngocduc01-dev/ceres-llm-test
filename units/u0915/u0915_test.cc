// FILE: u0915_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  object.LeftMultiplyAndAccumulate(a0, a1);
}

// P2: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  double a0[5] = {};
  double a1[5] = {};
  object.LeftMultiplyAndAccumulate(a0, a1);
}

