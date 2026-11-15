// FILE: u1235_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/block_sparse_matrix.cc"

// P1: START -> 1 -> END
TEST(CreateStructureOfCompressedRowSparseMatrixTest, TC1_CallsTarget) {
  double a0[5] = {};
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  CreateStructureOfCompressedRowSparseMatrix(a0, a1, a2, a3, nullptr);
}

// P2: START -> 1 -> END
TEST(CreateStructureOfCompressedRowSparseMatrixTest, TC2_CallsTarget) {
  double a0[5] = {};
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  CreateStructureOfCompressedRowSparseMatrix(a0, a1, a2, a3, nullptr);
}

// P3: START -> 1 -> END
TEST(CreateStructureOfCompressedRowSparseMatrixTest, TC3_CallsTarget) {
  double a0[5] = {};
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  CreateStructureOfCompressedRowSparseMatrix(a0, a1, a2, a3, nullptr);
}

