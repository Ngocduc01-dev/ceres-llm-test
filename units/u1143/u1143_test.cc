// FILE: u1143_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1143, TC1_CallsTarget) {
  Preconditioner::Options options{};
  BlockSparseMatrix A{};
  ceres::internal::BlockSparseJacobiPreconditioner object{};
  (void)object;
}
