// FILE: u0018_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BiCubicInterpolatorEvaluate, TC1_P1_SingleStatement) {
  const double data[4] = {1.0, 2.0, 3.0, 4.0};
  ceres::Grid2D<double, 1> grid(data, 0, 2, 0, 2);
  ceres::BiCubicInterpolator<ceres::Grid2D<double, 1>> interpolator(grid);

  const double r = 0.4;
  const double c = 0.7;
  double f[1] = {0.0};

  interpolator.Evaluate(r, c, f);
}
