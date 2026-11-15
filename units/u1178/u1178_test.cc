// FILE: u1178_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(AppendRowsTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix & B a0{};
  object.AppendRows(a0);
}

// P2: START -> 1 -> END
TEST(AppendRowsTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix & B a0{};
  object.AppendRows(a0);
}

