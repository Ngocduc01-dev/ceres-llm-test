// FILE: u1218_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1218, TC1_CallsTarget) {
  BlockSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateRandomMatrix(options, prng, use_page_locked_memory);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1218, TC2_CallsTarget) {
  BlockSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateRandomMatrix(options, prng, use_page_locked_memory);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1218, TC3_CallsTarget) {
  BlockSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateRandomMatrix(options, prng, use_page_locked_memory);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1218, TC4_CallsTarget) {
  BlockSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateRandomMatrix(options, prng, use_page_locked_memory);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1218, TC5_CallsTarget) {
  BlockSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateRandomMatrix(options, prng, use_page_locked_memory);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1218, TC6_CallsTarget) {
  BlockSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateRandomMatrix(options, prng, use_page_locked_memory);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1218, TC7_CallsTarget) {
  BlockSparseMatrix::RandomMatrixOptions options{};
  std::mt19937 prng{};
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  object.CreateRandomMatrix(options, prng, use_page_locked_memory);
}
