// FILE: u1092_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1092, TC1_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.RightMultiplyAndAccumulateF(nullptr, nullptr);
}
