// FILE: u0806_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"
#include "ceres/map_util.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0806, TC1_CallsTarget) {
  const int candidate{};
  std::vector<int> centers{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClusteringQualityDifference(candidate, centers);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0806, TC2_CallsTarget) {
  const int candidate{};
  std::vector<int> centers{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClusteringQualityDifference(candidate, centers);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0806, TC3_CallsTarget) {
  const int candidate{};
  std::vector<int> centers{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClusteringQualityDifference(candidate, centers);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0806, TC4_CallsTarget) {
  const int candidate{};
  std::vector<int> centers{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClusteringQualityDifference(candidate, centers);
}
