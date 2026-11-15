// FILE: u1286_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"

// P1: START -> 1 -> END
TEST(u1286_Test, TC1_CallsTarget) {
  ComputeCanonicalViewsClustering(nullptr, nullptr, nullptr, nullptr);
}
