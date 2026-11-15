// FILE: u0808_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"
#include "ceres/map_util.h"

// P1: START -> 1 -> END
TEST(ComputeClusterMembershipTest, TC1_CallsTarget) {
  CanonicalViewsClustering object{};
  int a0 = 0;
  int a1[5] = {};
  object.ComputeClusterMembership(a0, a1);
}

// P2: START -> 1 -> END
TEST(ComputeClusterMembershipTest, TC2_CallsTarget) {
  CanonicalViewsClustering object{};
  int a0 = 0;
  int a1[5] = {};
  object.ComputeClusterMembership(a0, a1);
}

// P3: START -> 1 -> END
TEST(ComputeClusterMembershipTest, TC3_CallsTarget) {
  CanonicalViewsClustering object{};
  int a0 = 0;
  int a1[5] = {};
  object.ComputeClusterMembership(a0, a1);
}

