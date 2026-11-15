// FILE: u0315_test.cc
#include "gtest/gtest.h"
#define private public
#include "ceres/inner_product_computer.h"
#undef private

TEST(Unit_u0315, PathP1) {
  ceres::internal::InnerProductComputer::ProductTerm target(1, 2, 3);
  EXPECT_EQ(target.row, 1);
  EXPECT_EQ(target.col, 2);
  EXPECT_EQ(target.index, 3);
}
