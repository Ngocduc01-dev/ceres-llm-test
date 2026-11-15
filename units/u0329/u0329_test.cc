// FILE: u0329_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"

TEST(Unit_u0329, PathP1) {
  ceres::internal::LinearLeastSquaresProblem target;
  EXPECT_EQ(target.num_eliminate_blocks, 0);
}
