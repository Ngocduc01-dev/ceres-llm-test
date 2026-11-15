// FILE: u0311_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include <cmath>

TEST(Unit_u0311, PathP1) {
  EXPECT_TRUE(std::isnan(ceres::internal::WeightedGraph<int>::InvalidWeight()));
}
