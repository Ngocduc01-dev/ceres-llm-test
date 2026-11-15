// FILE: u0326_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

TEST(Unit_u0326, PathP1) {
  ceres::internal::LineSearchFunction target(nullptr);
  EXPECT_TRUE(target.direction().size() == 0);
}
