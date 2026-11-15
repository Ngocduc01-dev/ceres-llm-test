// FILE: u1197_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(UpdateBlockDiagonalFtFMultiThreadedTest, TC1_CallsTarget) {
  PartitionedMatrixView object{};
  object.UpdateBlockDiagonalFtFMultiThreaded(nullptr);
}

