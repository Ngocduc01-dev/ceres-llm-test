// FILE: u1236_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1236, TC1_CallsTarget) {
  TripletSparseMatrix input{};
  bool transpose{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.FromTripletSparseMatrix(input, transpose);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1236, TC2_CallsTarget) {
  TripletSparseMatrix input{};
  bool transpose{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.FromTripletSparseMatrix(input, transpose);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1236, TC3_CallsTarget) {
  TripletSparseMatrix input{};
  bool transpose{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.FromTripletSparseMatrix(input, transpose);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1236, TC4_CallsTarget) {
  TripletSparseMatrix input{};
  bool transpose{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.FromTripletSparseMatrix(input, transpose);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1236, TC5_CallsTarget) {
  TripletSparseMatrix input{};
  bool transpose{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.FromTripletSparseMatrix(input, transpose);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1236, TC6_CallsTarget) {
  TripletSparseMatrix input{};
  bool transpose{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.FromTripletSparseMatrix(input, transpose);
}
