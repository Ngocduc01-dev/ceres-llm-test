// FILE: u0781_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"
#include "ceres/single_linkage_clustering.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0781, TC1_CallsTarget) {
  SingleLinkageClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::ComputeSingleLinkageClustering(options, graph, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0781, TC2_CallsTarget) {
  SingleLinkageClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::ComputeSingleLinkageClustering(options, graph, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0781, TC3_CallsTarget) {
  SingleLinkageClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::ComputeSingleLinkageClustering(options, graph, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0781, TC4_CallsTarget) {
  SingleLinkageClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::ComputeSingleLinkageClustering(options, graph, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0781, TC5_CallsTarget) {
  SingleLinkageClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::ComputeSingleLinkageClustering(options, graph, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u0781, TC6_CallsTarget) {
  SingleLinkageClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::ComputeSingleLinkageClustering(options, graph, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u0781, TC7_CallsTarget) {
  SingleLinkageClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::ComputeSingleLinkageClustering(options, graph, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u0781, TC8_CallsTarget) {
  SingleLinkageClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::ComputeSingleLinkageClustering(options, graph, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u0781, TC9_CallsTarget) {
  SingleLinkageClusteringOptions options{};
  WeightedGraph<int> graph{};
  ceres::internal::ComputeSingleLinkageClustering(options, graph, nullptr);
}
