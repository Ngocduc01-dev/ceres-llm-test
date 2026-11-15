// FILE: u0988_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0988, TC1_CallsTarget) {
  ceres::internal::BlockCRSJacobiPreconditioner object{};
  object.num_cols();
}
