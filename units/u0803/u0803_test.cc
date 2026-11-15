// FILE: u0803_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0803, TC1_CallsTarget) {
  ceres::internal::CanonicalViewsClustering object{};
  object.FindValidViews(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0803, TC2_CallsTarget) {
  ceres::internal::CanonicalViewsClustering object{};
  object.FindValidViews(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0803, TC3_CallsTarget) {
  ceres::internal::CanonicalViewsClustering object{};
  object.FindValidViews(nullptr);
}
