// FILE: u0457_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0457, PathP1) {
  const T arg_0 = 1;
  ceres::OrderedGroups<double *> target(arg_0);
  target.GroupId(0);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0457, PathP2) {
  const T arg_0 = 1;
  ceres::OrderedGroups<double *> target(arg_0);
  target.GroupId(0);
}
