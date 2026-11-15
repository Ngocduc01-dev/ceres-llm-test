// FILE: u1424_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"

// P1: START -> 1 -> END
TEST(u1424_Test, TC1_CallsTarget) {
  PartitionedMatrixView<> target{};
  target.CreateBlockDiagonalEtE();
}
