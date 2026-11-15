// FILE: u1371_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_jacobi_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1371_Test, TC1_CallsTarget) {
  ceres::internal::SchurJacobiPreconditioner target{};
  target.UpdateImpl(nullptr, nullptr);
}
