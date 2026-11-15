// FILE: u1372_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parallel_for.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(u1372_Test, TC1_CallsTarget) {
  ceres::internal::BlockSparseJacobiPreconditioner target{};
  target.UpdateImpl(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1372_Test, TC2_CallsTarget) {
  ceres::internal::BlockSparseJacobiPreconditioner target{};
  target.UpdateImpl(nullptr, nullptr);
}
