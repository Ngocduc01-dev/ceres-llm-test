// FILE: u1196_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(UpdateBlockDiagonalFtFSingleThreadedTest, TC1_CallsTarget) {
  PartitionedMatrixView object{};
  object.UpdateBlockDiagonalFtFSingleThreaded(nullptr);
}

// P2: START -> 1 -> END
TEST(UpdateBlockDiagonalFtFSingleThreadedTest, TC2_CallsTarget) {
  PartitionedMatrixView object{};
  object.UpdateBlockDiagonalFtFSingleThreaded(nullptr);
}

// P3: START -> 1 -> END
TEST(UpdateBlockDiagonalFtFSingleThreadedTest, TC3_CallsTarget) {
  PartitionedMatrixView object{};
  object.UpdateBlockDiagonalFtFSingleThreaded(nullptr);
}

