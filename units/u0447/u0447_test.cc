// FILE: u0447_test.cc
#include "gtest/gtest.h"
#include <utility>

#include "ceres/internal/autodiff.h"
#include "ceres/jet.h"

TEST(Unit_u0447, CopiesRequestedJacobianBlocks) {
  using Jet = ceres::Jet<double, 3>;
  Jet output[1];
  output[0].v[0] = 2.0;
  output[0].v[1] = 3.0;
  output[0].v[2] = 5.0;
  double first[1] = {};
  double second[2] = {};
  double* jacobians[] = {first, second};

  ceres::internal::Take1stOrderParts<std::integer_sequence<int, 1, 2>>::
      Apply(1, output, jacobians);

  EXPECT_DOUBLE_EQ(first[0], 2.0);
  EXPECT_DOUBLE_EQ(second[0], 3.0);
  EXPECT_DOUBLE_EQ(second[1], 5.0);
}
