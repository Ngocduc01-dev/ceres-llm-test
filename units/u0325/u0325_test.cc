// FILE: u0325_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

TEST(Unit_u0325, PathP1) {
  ceres::internal::LineSearchFunction target(nullptr);
  EXPECT_TRUE(target.position().size() == 0);
}
