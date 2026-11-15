// FILE: u0823_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(matrixTest, TC1_CallsTarget) {
  BlockCRSJacobiPreconditioner object{};
  object.matrix();
}

