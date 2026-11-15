// FILE: u1231_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END
TEST(UpdateImplTest, TC1_CallsTarget) {
  BlockCRSJacobiPreconditioner object{};
  CompressedRowSparseMatrix & A a0{};
  double a1[5] = {};
  object.UpdateImpl(a0, a1);
}

