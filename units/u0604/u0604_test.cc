// FILE: u0604_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"
#include "ceres/map_util.h"

// Path P1 calls UpdateCanonicalViewAssignments(const int canonical_view).
TEST(Unitu0604, CallsTarget) {
  object.UpdateCanonicalViewAssignments(1);
}
