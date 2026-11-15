// FILE: u1179_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(AppendColsTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix & B a0{};
  object.AppendCols(a0);
}

// P2: START -> 1 -> END
TEST(AppendColsTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix & B a0{};
  object.AppendCols(a0);
}

