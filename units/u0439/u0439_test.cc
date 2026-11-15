// FILE: u0439_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

TEST(Unit_u0439, EvaluatesJet) {
  const double data[5] = {0.0, 1.0, 2.0, 3.0, 4.0};
  ceres::Grid1D<double, 1> grid(data, 0, 5);
  ceres::CubicInterpolator<ceres::Grid1D<double, 1>> interpolator(grid);

  ceres::Jet<double, 1> x(1.7);
  x.v[0] = 1.0;
  ceres::Jet<double, 1> f[1];
  interpolator.Evaluate(x, f);

  EXPECT_NEAR(f[0].a, 1.7, 1e-12);
  EXPECT_NEAR(f[0].v[0], 1.0, 1e-12);
}
