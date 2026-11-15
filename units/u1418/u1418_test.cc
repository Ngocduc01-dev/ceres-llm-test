// FILE: u1418_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/single_linkage_clustering.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1418, TC1_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ClusterCameras(visibility);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1418, TC2_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ClusterCameras(visibility);
}
