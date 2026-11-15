// FILE: u1479_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/graph_algorithms.h"
#include "ceres/visibility.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1479_Test, TC1_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.ComputeClusterTridiagonalSparsity(nullptr);
}
