// FILE: u1327_test.cc
#include "gtest/gtest.h"
#include "ceres/fake_bundle_adjustment_jacobian.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END
TEST(u1327_Test, TC1_CallsTarget) {
  CreateFakeBundleAdjustmentPartitionedJacobian(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
