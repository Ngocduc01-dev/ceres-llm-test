// FILE: u0934_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ToTextFileTest, TC1_CallsTarget) {
  CompressedRowSparseMatrix object{};
  object.ToTextFile(nullptr);
}

// P2: START -> 1 -> END
TEST(ToTextFileTest, TC2_CallsTarget) {
  CompressedRowSparseMatrix object{};
  object.ToTextFile(nullptr);
}

// P3: START -> 1 -> END
TEST(ToTextFileTest, TC3_CallsTarget) {
  CompressedRowSparseMatrix object{};
  object.ToTextFile(nullptr);
}

