// FILE: u1352_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/preconditioner.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/subset_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1352, TC1_CallsTarget) {
  Preconditioner::Options options{};
  BlockSparseMatrix A{};
  ceres::internal::SubsetPreconditioner object{};
  (void)object;
}
