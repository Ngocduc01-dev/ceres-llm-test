// FILE: u0373_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0373, PathP1) {
  ceres::PartitionedMatrixView<2> target;
  target.num_col_blocks_e();
}
