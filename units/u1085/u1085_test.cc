// FILE: u1085_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(GetCellTest, TC1_CallsTarget) {
  BlockRandomAccessDiagonalMatrix object{};
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
  BlockRandomAccessDiagonalMatrix object{};
  int a0 = 0;
  int a1 = 0;
  int a2[5] = {};
  int a3[5] = {};
  int a4[5] = {};
  int a5[5] = {};
  object.GetCell(a0, a1, a2, a3, a4, a5);
}

