// FILE: u0350_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include <map>

// Path P1: START -> 1 -> END.
TEST(Unit_u0350, PathP1) {
  std::map<int, int> collection;
  ceres::InsertIfNotPresent(&collection, 1, 2);
}
