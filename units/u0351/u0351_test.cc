// FILE: u0351_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include <set>

// Path P1: START -> 1 -> END.
TEST(Unit_u0351, PathP1) {
  std::set<int> collection;
  ceres::ContainsKey(collection, 1);
}
