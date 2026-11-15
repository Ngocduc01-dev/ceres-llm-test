// FILE: u1163_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"

// P1: START -> 1 -> END
TEST(UpdateBlockDiagonalEtESingleThreadedTest, TC1_CallsTarget) {
  PartitionedMatrixView object{};
  object.UpdateBlockDiagonalEtESingleThreaded(nullptr);
}

// P2: START -> 1 -> END
TEST(UpdateBlockDiagonalEtESingleThreadedTest, TC2_CallsTarget) {
  PartitionedMatrixView object{};
  object.UpdateBlockDiagonalEtESingleThreaded(nullptr);
}

