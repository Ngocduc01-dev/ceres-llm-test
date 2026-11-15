// FILE: u0950_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ResizeTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  int a0 = 0;
  int a1 = 0;
  object.Resize(a0, a1);
}

// P2: START -> 1 -> END
TEST(ResizeTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  int a0 = 0;
  int a1 = 0;
  object.Resize(a0, a1);
}

// P3: START -> 1 -> END
TEST(ResizeTest, TC3_CallsTarget) {
  TripletSparseMatrix object{};
  int a0 = 0;
  int a1 = 0;
  object.Resize(a0, a1);
}

