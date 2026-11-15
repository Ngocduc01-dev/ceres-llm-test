// FILE: u1211_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(AppendRowsTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  BlockSparseMatrix & m a0{};
  object.AppendRows(a0);
}

// P2: START -> 1 -> END
TEST(AppendRowsTest, TC2_CallsTarget) {
  BlockSparseMatrix object{};
  BlockSparseMatrix & m a0{};
  object.AppendRows(a0);
}

// P3: START -> 1 -> END
TEST(AppendRowsTest, TC3_CallsTarget) {
  BlockSparseMatrix object{};
  BlockSparseMatrix & m a0{};
  object.AppendRows(a0);
}

