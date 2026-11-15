// FILE: u0017_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CubicInterpolatorEvaluate, TC1_P1_SingleNode) {
  const double data[5] = {1.0, 3.0, 2.0, 5.0, 4.0};
  ceres::Grid1D<double, 1> grid(data, 0, 5);
  ceres::CubicInterpolator<ceres::Grid1D<double, 1>> interpolator(grid);

  const double x = 1.7;
  double f[1] = {0.0};
  interpolator.Evaluate(x, f);
}
