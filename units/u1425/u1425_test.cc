// FILE: u1425_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"

// P1: START -> 1 -> END
TEST(u1425_Test, TC1_CallsTarget) {
  PartitionedMatrixView<> target{};
  target.CreateBlockDiagonalFtF();
}
