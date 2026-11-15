// FILE: u1286_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1286, TC1_CallsTarget) {
  CanonicalViewsClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::ComputeCanonicalViewsClustering(options, graph, nullptr, nullptr);
}
