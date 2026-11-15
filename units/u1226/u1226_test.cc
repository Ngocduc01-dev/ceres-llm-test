// FILE: u1226_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"

// P1: START -> 1 -> END
TEST(CreateBlockDiagonalMatrixLayoutTest, TC1_CallsTarget) {
  PartitionedMatrixView object{};
  int a0 = 0;
  int a1 = 0;
  object.CreateBlockDiagonalMatrixLayout(a0, a1);
}

// P2: START -> 1 -> END
TEST(CreateBlockDiagonalMatrixLayoutTest, TC2_CallsTarget) {
  PartitionedMatrixView object{};
  int a0 = 0;
  int a1 = 0;
  object.CreateBlockDiagonalMatrixLayout(a0, a1);
}

