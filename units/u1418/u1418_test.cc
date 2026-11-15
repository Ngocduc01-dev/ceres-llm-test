// FILE: u1418_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/single_linkage_clustering.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1418_Test, TC1_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.ClusterCameras(nullptr);
}

// P2: START -> 1 -> END
TEST(u1418_Test, TC2_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.ClusterCameras(nullptr);
}
