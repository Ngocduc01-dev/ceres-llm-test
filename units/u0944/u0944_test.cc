// FILE: u0944_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ToTextFileTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  object.ToTextFile(nullptr);
}

// P2: START -> 1 -> END
TEST(ToTextFileTest, TC2_CallsTarget) {
  BlockSparseMatrix object{};
  object.ToTextFile(nullptr);
}

// P3: START -> 1 -> END
TEST(ToTextFileTest, TC3_CallsTarget) {
  BlockSparseMatrix object{};
  object.ToTextFile(nullptr);
}

