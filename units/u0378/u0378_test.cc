// FILE: u0378_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0378, PathP1) {
  ceres::PartitionedMatrixView<2> target;
  target.f_cols_partition();
}
