// FILE: u0604_test.cc
#include "gtest/gtest.h"
#include "ceres/canonical_views_clustering.h"
#include "ceres/graph.h"
#include "ceres/map_util.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0604, CallsTarget) {
  object.UpdateCanonicalViewAssignments(1);
}
