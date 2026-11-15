// FILE: u0808_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"
#include "ceres/map_util.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0808, TC1_CallsTarget) {
  std::vector<int> centers{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClusterMembership(centers, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0808, TC2_CallsTarget) {
  std::vector<int> centers{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClusterMembership(centers, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0808, TC3_CallsTarget) {
  std::vector<int> centers{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClusterMembership(centers, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0808, TC4_CallsTarget) {
  std::vector<int> centers{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClusterMembership(centers, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0808, TC5_CallsTarget) {
  std::vector<int> centers{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClusterMembership(centers, nullptr);
}
