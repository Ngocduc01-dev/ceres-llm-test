// FILE: u0748_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

// Path P1: START -> 1 -> 2 -> 3 -> 4 -> END.
TEST(Unit_u0748, PathP1) {
  ceres::internal::Graph<int> target;
  target.AddVertex(1);
  target.AddVertex(2);
  target.AddEdge(1, 2);
}
