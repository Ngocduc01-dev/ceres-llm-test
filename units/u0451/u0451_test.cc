// FILE: u0451_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

TEST(Unit_u0451, CopiesSignAndDerivative) {
  ceres::Jet<double, 1> f(-2.0);
  ceres::Jet<double, 1> g(-3.0);
  f.v[0] = 1.0;
  g.v[0] = 1.0;

  const ceres::Jet<double, 1> result = ceres::copysign(f, g);

  EXPECT_DOUBLE_EQ(result.a, -2.0);
  EXPECT_DOUBLE_EQ(result.v[0], 1.0);
}
