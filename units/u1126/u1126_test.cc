// FILE: u1126_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"

// P1: START -> 1 -> END
TEST(ComputeClusteringTest, TC1_CallsTarget) {
  CanonicalViewsClustering object{};
  CanonicalViewsClusteringOptions & options a0{};
  int a1 = 0;
  int a2[5] = {};
  int a3[5] = {};
  object.ComputeClustering(a0, a1, a2, a3);
}

// P2: START -> 1 -> END
TEST(ComputeClusteringTest, TC2_CallsTarget) {
  CanonicalViewsClustering object{};
  CanonicalViewsClusteringOptions & options a0{};
  int a1 = 0;
  int a2[5] = {};
  int a3[5] = {};
  object.ComputeClustering(a0, a1, a2, a3);
}

// P3: START -> 1 -> END
TEST(ComputeClusteringTest, TC3_CallsTarget) {
  CanonicalViewsClustering object{};
  CanonicalViewsClusteringOptions & options a0{};
  int a1 = 0;
  int a2[5] = {};
  int a3[5] = {};
  object.ComputeClustering(a0, a1, a2, a3);
}

