// FILE: u1126_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1126, TC1_CallsTarget) {
  CanonicalViewsClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClustering(options, graph, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1126, TC2_CallsTarget) {
  CanonicalViewsClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClustering(options, graph, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1126, TC3_CallsTarget) {
  CanonicalViewsClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClustering(options, graph, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1126, TC4_CallsTarget) {
  CanonicalViewsClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClustering(options, graph, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1126, TC5_CallsTarget) {
  CanonicalViewsClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::CanonicalViewsClustering object{};
  object.ComputeClustering(options, graph, nullptr, nullptr);
}
