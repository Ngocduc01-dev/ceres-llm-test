// FILE: u0473_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include <unordered_map>

// Path P1: START -> 1 -> END.
TEST(Unit_u0473, PathP1) {
  std::unordered_map<int, double> collection;
  collection.emplace(1, 2.0);
  ceres::FindOrDie(collection, 1);
}
