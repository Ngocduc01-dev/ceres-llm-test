// FILE: u1328_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/fake_bundle_adjustment_jacobian.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END
TEST(u1328_Test, TC1_CallsTarget) {
  CreateFakeBundleAdjustmentPartitionedJacobian(nullptr, nullptr, nullptr, nullptr);
}
