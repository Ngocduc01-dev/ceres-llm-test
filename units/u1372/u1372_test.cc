// FILE: u1372_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parallel_for.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1372, TC1_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::BlockSparseJacobiPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1372, TC2_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::BlockSparseJacobiPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}
