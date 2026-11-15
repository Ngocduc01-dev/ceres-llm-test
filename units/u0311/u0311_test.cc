// FILE: u0311_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0311, PathP1) {
  ceres::WeightedGraph<int> target;
  target.InvalidWeight();
}
