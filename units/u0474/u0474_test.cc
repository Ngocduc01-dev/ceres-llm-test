// FILE: u0474_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include <unordered_map>

// Path P1: START -> 1 -> END.
TEST(Unit_u0474, PathP1) {
  std::unordered_map<int, double> collection;
  collection.emplace(1, 2);
  ceres::FindWithDefault(collection, 2, 3.0);
}
