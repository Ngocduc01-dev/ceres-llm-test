// FILE: u0987_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(num_rowsTest, TC1_CallsTarget) {
  BlockCRSJacobiPreconditioner object{};
  object.num_rows();
}

