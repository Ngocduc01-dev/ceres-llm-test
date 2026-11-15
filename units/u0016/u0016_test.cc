// FILE: u0016_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CubicInterpolatorEvaluate, TC1_P1_SinglePath) {
  const double data[5] = {0.5, 1.5, 2.5, 3.5, 4.5};
  ceres::Grid1D<double> grid(data, 0, 5);
  ceres::CubicInterpolator<ceres::Grid1D<double>> interpolator(grid);

  const double x = 1.37;
  double f = 0.0;
  double dfdx = 0.0;
  interpolator.Evaluate(x, &f, &dfdx);
}
