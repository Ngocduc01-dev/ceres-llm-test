// FILE: u1242_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/block_random_access_diagonal_matrix.h"

// P1: START -> 1 -> END
TEST(num_colsTest, TC1_CallsTarget) {
  BlockSparseJacobiPreconditioner object{};
  object.num_cols();
}

