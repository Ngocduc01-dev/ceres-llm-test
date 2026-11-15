// FILE: u0458_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0458, PathP1) {
  const int arg_0 = 1;
  ceres::OrderedGroups<double *> target(arg_0);
  target.GroupSize(1);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0458, PathP2) {
  const int arg_0 = 1;
  ceres::OrderedGroups<double *> target(arg_0);
  target.GroupSize(1);
}
