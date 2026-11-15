// FILE: u0715_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

// Path P1: START -> 1 -> 2 -> END.
TEST(Unit_u0715, PathP1) {
  ceres::internal::WeightedGraph<int> target;
  target.AddVertex(1);
  target.AddVertex(2);
  target.EdgeWeight(1, 2);
}
