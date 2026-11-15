// FILE: u0781_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"
#include "ceres/single_linkage_clustering.h"

// P1: START -> 1 -> END
TEST(ComputeSingleLinkageClusteringTest, TC1_CallsTarget) {
  SingleLinkageClusteringOptions & options a0{};
  int a1 = 0;
  int a2[5] = {};
  ceres::internal::ComputeSingleLinkageClustering(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(ComputeSingleLinkageClusteringTest, TC2_CallsTarget) {
  SingleLinkageClusteringOptions & options a0{};
  int a1 = 0;
  int a2[5] = {};
  ceres::internal::ComputeSingleLinkageClustering(a0, a1, a2);
}

// P3: START -> 1 -> END
TEST(ComputeSingleLinkageClusteringTest, TC3_CallsTarget) {
  SingleLinkageClusteringOptions & options a0{};
  int a1 = 0;
  int a2[5] = {};
  ceres::internal::ComputeSingleLinkageClustering(a0, a1, a2);
}

