// FILE: u1015_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1015, TC1_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.num_cols();
}
