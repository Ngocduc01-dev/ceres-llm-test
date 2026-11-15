// FILE: u1218_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(CreateRandomMatrixTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  BlockSparseMatrix::RandomMatrixOptions & options a0{};
  std::mt19937 & prng a1{};
  bool a2 = false;
  object.CreateRandomMatrix(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(CreateRandomMatrixTest, TC2_CallsTarget) {
  BlockSparseMatrix object{};
  BlockSparseMatrix::RandomMatrixOptions & options a0{};
  std::mt19937 & prng a1{};
  bool a2 = false;
  object.CreateRandomMatrix(a0, a1, a2);
}

// P3: START -> 1 -> END
TEST(CreateRandomMatrixTest, TC3_CallsTarget) {
  BlockSparseMatrix object{};
  BlockSparseMatrix::RandomMatrixOptions & options a0{};
  std::mt19937 & prng a1{};
  bool a2 = false;
  object.CreateRandomMatrix(a0, a1, a2);
}

