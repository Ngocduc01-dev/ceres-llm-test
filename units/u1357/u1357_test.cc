// FILE: u1357_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"

// P1: START -> 1 -> END
TEST(u1357_Test, TC1_CallsTarget) {
  PartitionedMatrixView<> target{};
  target.UpdateBlockDiagonalFtF(nullptr);
}

// P2: START -> 1 -> END
TEST(u1357_Test, TC2_CallsTarget) {
  PartitionedMatrixView<> target{};
  target.UpdateBlockDiagonalFtF(nullptr);
}
