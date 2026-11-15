// FILE: u0660_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1 calls DenseSparseMatrix(int num_rows, int num_cols).
TEST(Unitu0660, CallsTarget) {
  object.DenseSparseMatrix(1, 1);
}
