// FILE: u0309_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

TEST(Unit_u0309, PathP1) {
  ceres::internal::Graph<int> target;
  EXPECT_TRUE(target.vertices().empty());
}
