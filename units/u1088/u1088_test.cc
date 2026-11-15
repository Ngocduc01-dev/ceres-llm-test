// FILE: u1088_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"

// P1: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateESingleThreadedTest, TC1_CallsTarget) {
  PartitionedMatrixView object{};
  double a0[5] = {};
  double a1[5] = {};
  object.LeftMultiplyAndAccumulateESingleThreaded(a0, a1);
}

// P2: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateESingleThreadedTest, TC2_CallsTarget) {
  PartitionedMatrixView object{};
  double a0[5] = {};
  double a1[5] = {};
  object.LeftMultiplyAndAccumulateESingleThreaded(a0, a1);
}

