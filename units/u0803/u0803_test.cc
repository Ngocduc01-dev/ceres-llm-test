// FILE: u0803_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"

// P1: START -> 1 -> END
TEST(FindValidViewsTest, TC1_CallsTarget) {
  CanonicalViewsClustering object{};
  int a0[5] = {};
  object.FindValidViews(a0);
}

// P2: START -> 1 -> END
TEST(FindValidViewsTest, TC2_CallsTarget) {
  CanonicalViewsClustering object{};
  int a0[5] = {};
  object.FindValidViews(a0);
}

// P3: START -> 1 -> END
TEST(FindValidViewsTest, TC3_CallsTarget) {
  CanonicalViewsClustering object{};
  int a0[5] = {};
  object.FindValidViews(a0);
}

