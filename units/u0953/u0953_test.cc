// FILE: u0953_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(CreateRandomMatrixTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix::RandomMatrixOptions & options a0{};
  std::mt19937 & prng a1{};
  object.CreateRandomMatrix(a0, a1);
}

// P2: START -> 1 -> END
TEST(CreateRandomMatrixTest, TC2_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix::RandomMatrixOptions & options a0{};
  std::mt19937 & prng a1{};
  object.CreateRandomMatrix(a0, a1);
}

// P3: START -> 1 -> END
TEST(CreateRandomMatrixTest, TC3_CallsTarget) {
  TripletSparseMatrix object{};
  TripletSparseMatrix::RandomMatrixOptions & options a0{};
  std::mt19937 & prng a1{};
  object.CreateRandomMatrix(a0, a1);
}

