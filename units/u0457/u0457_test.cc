// FILE: u0457_test.cc
#include "gtest/gtest.h"
TEST(Unit_u0457, GroupId) {
  ceres::OrderedGroups<double*> target;
  target.GroupId(nullptr);
}
