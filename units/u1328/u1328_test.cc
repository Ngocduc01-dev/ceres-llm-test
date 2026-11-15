// FILE: u1328_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/fake_bundle_adjustment_jacobian.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1328, TC1_CallsTarget) {
  int num_cameras{};
  int num_points{};
  double visibility{};
  std::mt19937 rng{};
  ceres::internal::CreateFakeBundleAdjustmentPartitionedJacobian(num_cameras, num_points, visibility, rng);
}
