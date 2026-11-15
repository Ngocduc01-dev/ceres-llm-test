// FILE: u1236_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(FromTripletSparseMatrixTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  TripletSparseMatrix & input a0{};
  bool a1 = false;
  object.FromTripletSparseMatrix(a0, a1);
}

// P2: START -> 1 -> END
TEST(FromTripletSparseMatrixTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  TripletSparseMatrix & input a0{};
  bool a1 = false;
  object.FromTripletSparseMatrix(a0, a1);
}

// P3: START -> 1 -> END
TEST(FromTripletSparseMatrixTest, TC3_CallsTarget) {
  CompressedRowSparseMatrix object{};
  TripletSparseMatrix & input a0{};
  bool a1 = false;
  object.FromTripletSparseMatrix(a0, a1);
}

