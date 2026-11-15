// FILE: u1207_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(DeleteRowBlocksTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  int a0 = 0;
  object.DeleteRowBlocks(a0);
}

// P2: START -> 1 -> END
TEST(DeleteRowBlocksTest, TC2_CallsTarget) {
  BlockSparseMatrix object{};
  int a0 = 0;
  object.DeleteRowBlocks(a0);
}

// P3: START -> 1 -> END
TEST(DeleteRowBlocksTest, TC3_CallsTarget) {
  BlockSparseMatrix object{};
  int a0 = 0;
  object.DeleteRowBlocks(a0);
}

