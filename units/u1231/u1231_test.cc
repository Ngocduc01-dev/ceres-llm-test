// FILE: u1231_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1231, TC1_CallsTarget) {
  CompressedRowSparseMatrix A{};
  ceres::internal::BlockCRSJacobiPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}
