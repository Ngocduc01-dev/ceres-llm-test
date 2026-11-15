// FILE: u0809_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0809, TC1_CallsTarget) {
  std::vector<std::set<int>> cluster_visibility{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.CreateClusterGraph(cluster_visibility);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0809, TC2_CallsTarget) {
  std::vector<std::set<int>> cluster_visibility{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.CreateClusterGraph(cluster_visibility);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0809, TC3_CallsTarget) {
  std::vector<std::set<int>> cluster_visibility{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.CreateClusterGraph(cluster_visibility);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0809, TC4_CallsTarget) {
  std::vector<std::set<int>> cluster_visibility{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.CreateClusterGraph(cluster_visibility);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0809, TC5_CallsTarget) {
  std::vector<std::set<int>> cluster_visibility{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.CreateClusterGraph(cluster_visibility);
}
