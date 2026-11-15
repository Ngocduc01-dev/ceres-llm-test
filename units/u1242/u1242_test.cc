// FILE: u1242_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/block_random_access_diagonal_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1242, TC1_CallsTarget) {
  ceres::internal::BlockSparseJacobiPreconditioner object{};
  object.num_cols();
}
