// FILE: u1115_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateFSingleThreadedTest, TC1_CallsTarget) {
  PartitionedMatrixView object{};
  double a0[5] = {};
  double a1[5] = {};
  object.LeftMultiplyAndAccumulateFSingleThreaded(a0, a1);
}

// P2: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateFSingleThreadedTest, TC2_CallsTarget) {
  PartitionedMatrixView object{};
  double a0[5] = {};
  double a1[5] = {};
  object.LeftMultiplyAndAccumulateFSingleThreaded(a0, a1);
}

// P3: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateFSingleThreadedTest, TC3_CallsTarget) {
  PartitionedMatrixView object{};
  double a0[5] = {};
  double a1[5] = {};
  object.LeftMultiplyAndAccumulateFSingleThreaded(a0, a1);
}

