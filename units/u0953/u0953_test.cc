// FILE: u0953_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0953, TC1_CallsTarget) {
  TripletSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::TripletSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0953, TC2_CallsTarget) {
  TripletSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::TripletSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0953, TC3_CallsTarget) {
  TripletSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::TripletSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0953, TC4_CallsTarget) {
  TripletSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::TripletSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0953, TC5_CallsTarget) {
  TripletSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::TripletSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}
