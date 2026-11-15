// FILE: u0823_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0823, TC1_CallsTarget) {
  ceres::internal::BlockCRSJacobiPreconditioner object{};
  object.matrix();
}
