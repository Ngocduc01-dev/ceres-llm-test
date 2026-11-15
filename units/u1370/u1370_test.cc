// FILE: u1370_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1370, TC1_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1370, TC2_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1370, TC3_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1370, TC4_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1370, TC5_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1370, TC6_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1370, TC7_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1370, TC8_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1370, TC9_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1370, TC10_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1370, TC11_CallsTarget) {
  CompressedRowSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.CreateRandomMatrix(options, prng);
}
