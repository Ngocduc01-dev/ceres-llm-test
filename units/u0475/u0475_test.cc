// FILE: u0475_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0475, PathP1) {
  std::map<int, int> collection{{1, 2}};
  ceres::FindOrNull(collection, 1);
}
