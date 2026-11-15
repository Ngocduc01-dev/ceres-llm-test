// FILE: u1092_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateFTest, TC1_CallsTarget) {
  PartitionedMatrixView object{};
  double a0[5] = {};
  double a1[5] = {};
  object.RightMultiplyAndAccumulateF(a0, a1);
}

