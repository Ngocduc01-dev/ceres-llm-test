// FILE: u1233_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/block_sparse_matrix.cc"

// P1: START -> 1 -> END
TEST(UpdateCompressedRowSparseMatrixImplTest, TC1_CallsTarget) {
  double a1[5] = {};
  UpdateCompressedRowSparseMatrixImpl(nullptr, a1, nullptr);
}

// P2: START -> 1 -> END
TEST(UpdateCompressedRowSparseMatrixImplTest, TC2_CallsTarget) {
  double a1[5] = {};
  UpdateCompressedRowSparseMatrixImpl(nullptr, a1, nullptr);
}

// P3: START -> 1 -> END
TEST(UpdateCompressedRowSparseMatrixImplTest, TC3_CallsTarget) {
  double a1[5] = {};
  UpdateCompressedRowSparseMatrixImpl(nullptr, a1, nullptr);
}

