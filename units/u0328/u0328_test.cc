// FILE: u0328_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_minimizer.h"

TEST(Unit_u0328, PathP1) {
  ceres::internal::LineSearchMinimizer::State target(1, 1);
  EXPECT_EQ(target.gradient.size(), 1);
  EXPECT_EQ(target.search_direction.size(), 1);
}
