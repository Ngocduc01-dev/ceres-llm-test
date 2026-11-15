// FILE: u1201_test.cc
#include "gtest/gtest.h"
#include "ceres/fake_bundle_adjustment_jacobian.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(CreateFakeBundleAdjustmentJacobianTest, TC1_CallsTarget) {
  int a0 = 0;
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  double a4 = 0.0;
  std::mt19937 & prng a5{};
  ceres::internal::CreateFakeBundleAdjustmentJacobian(a0, a1, a2, a3, a4, a5);
}

// P2: START -> 1 -> END
TEST(CreateFakeBundleAdjustmentJacobianTest, TC2_CallsTarget) {
  int a0 = 0;
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  double a4 = 0.0;
  std::mt19937 & prng a5{};
  ceres::internal::CreateFakeBundleAdjustmentJacobian(a0, a1, a2, a3, a4, a5);
}

// P3: START -> 1 -> END
TEST(CreateFakeBundleAdjustmentJacobianTest, TC3_CallsTarget) {
  int a0 = 0;
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  double a4 = 0.0;
  std::mt19937 & prng a5{};
  ceres::internal::CreateFakeBundleAdjustmentJacobian(a0, a1, a2, a3, a4, a5);
}

