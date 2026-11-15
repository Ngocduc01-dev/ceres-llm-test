// FILE: u0377_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0377, PathP1) {
  ceres::PartitionedMatrixView<2> target;
  target.e_cols_partition();
}
