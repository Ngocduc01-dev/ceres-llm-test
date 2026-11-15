// FILE: u1086_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_random_access_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(GetCellTest, TC1_CallsTarget) {
  BlockRandomAccessSparseMatrix object{};
  int a0 = 0;
  int a1 = 0;
  int a2[5] = {};
  int a3[5] = {};
  int a4[5] = {};
  int a5[5] = {};
  object.GetCell(a0, a1, a2, a3, a4, a5);
}

// P2: START -> 1 -> END
TEST(GetCellTest, TC2_CallsTarget) {
  BlockRandomAccessSparseMatrix object{};
  int a0 = 0;
  int a1 = 0;
  int a2[5] = {};
  int a3[5] = {};
  int a4[5] = {};
  int a5[5] = {};
  object.GetCell(a0, a1, a2, a3, a4, a5);
}

