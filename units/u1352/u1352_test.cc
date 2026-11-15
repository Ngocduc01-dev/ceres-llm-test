// FILE: u1352_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/preconditioner.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/subset_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1352_Test, TC1_CallsTarget) {
  ceres::internal::SubsetPreconditioner target{};
}
