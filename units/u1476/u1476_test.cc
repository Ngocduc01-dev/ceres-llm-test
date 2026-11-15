// FILE: u1476_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/visibility.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1476_Test, TC1_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.ComputeClusterJacobiSparsity(nullptr);
}

// P2: START -> 1 -> END
TEST(u1476_Test, TC2_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.ComputeClusterJacobiSparsity(nullptr);
}
