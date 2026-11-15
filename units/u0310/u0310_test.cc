// FILE: u0310_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

TEST(Unit_u0310, PathP1) {
  ceres::internal::WeightedGraph<int> target;
  EXPECT_TRUE(target.vertices().empty());
}
