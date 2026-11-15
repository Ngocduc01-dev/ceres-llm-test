// FILE: u0458_test.cc
#include "gtest/gtest.h"
TEST(Unit_u0458, GroupSize) {
  ceres::OrderedGroups<double*> target;
  target.GroupSize(0);
}
