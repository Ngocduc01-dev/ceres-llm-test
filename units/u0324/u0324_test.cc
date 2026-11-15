// FILE: u0324_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

TEST(Unit_u0324, PathP1) {
  ceres::internal::LineSearchFunction target(nullptr);
  EXPECT_DOUBLE_EQ(target.DirectionInfinityNorm(), 0.0);
}
