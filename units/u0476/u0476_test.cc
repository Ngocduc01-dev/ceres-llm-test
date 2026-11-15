// FILE: u0476_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include <unordered_map>

// Path P1: START -> 1 -> END.
TEST(Unit_u0476, PathP1) {
  std::unordered_map<int, int> collection;
  collection.emplace(1, 2);
  ceres::InsertOrDie(&collection, 1, 2);
}
