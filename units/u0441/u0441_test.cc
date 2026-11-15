// FILE: u0441_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

TEST(Unit_u0441, EvaluatesValueAndDerivative) {
  const double data[16] = {0.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 4.0,
                           2.0, 3.0, 4.0, 5.0, 3.0, 4.0, 5.0, 6.0};
  ceres::Grid2D<double, 1> grid(data, 0, 4, 0, 4);
  ceres::BiCubicInterpolator<ceres::Grid2D<double, 1>> interpolator(grid);

  double f[1] = {};
  double dfdr[1] = {};
  double dfdc[1] = {};
  interpolator.Evaluate(1.4, 1.6, f, dfdr, dfdc);

  EXPECT_NEAR(f[0], 3.0, 1e-12);
  EXPECT_NEAR(dfdr[0], 1.0, 1e-12);
  EXPECT_NEAR(dfdc[0], 1.0, 1e-12);
}
