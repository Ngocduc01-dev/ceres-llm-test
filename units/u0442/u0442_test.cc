// FILE: u0442_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

TEST(Unit_u0442, EvaluatesJet) {
  const double data[16] = {0.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 4.0,
                           2.0, 3.0, 4.0, 5.0, 3.0, 4.0, 5.0, 6.0};
  ceres::Grid2D<double, 1> grid(data, 0, 4, 0, 4);
  ceres::BiCubicInterpolator<ceres::Grid2D<double, 1>> interpolator(grid);

  ceres::Jet<double, 1> r(1.4);
  ceres::Jet<double, 1> c(1.6);
  r.v[0] = 1.0;
  c.v[0] = 2.0;
  ceres::Jet<double, 1> f[1];
  interpolator.Evaluate(r, c, f);

  EXPECT_NEAR(f[0].a, 3.0, 1e-12);
  EXPECT_NEAR(f[0].v[0], 3.0, 1e-12);
}
