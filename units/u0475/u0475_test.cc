// FILE: u0475_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include <map>

// Path P1: START -> 1 -> END.
TEST(Unit_u0475, PathP1) {
  std::map<int, int> collection{{1, 2}};
  ceres::FindOrNull(collection, 1);
}
