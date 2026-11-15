// FILE: u0441_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> 2 (đúng) -> 3 -> END
TEST(BiCubicInterpolatorEvaluate, DfdcNotNull) {
  const double data[4] = {1.0, 2.0, 3.0, 4.0};
  ceres::Grid2D<double> grid(data, 0, 2, 0, 2);
  ceres::BiCubicInterpolator<ceres::Grid2D<double>> interpolator(grid);

  double f = 0.0;
  double dfdr = 0.0;
  double dfdc = 0.0;
  interpolator.Evaluate(0.6, 1.3, &f, &dfdr, &dfdc);
}

// Path P2: START -> 1 -> 2 (sai) -> END
TEST(BiCubicInterpolatorEvaluate, DfdcNull) {
  const double data[4] = {1.0, 2.0, 3.0, 4.0};
  ceres::Grid2D<double> grid(data, 0, 2, 0, 2);
  ceres::BiCubicInterpolator<ceres::Grid2D<double>> interpolator(grid);

  double f = 0.0;
  double dfdr = 0.0;
  interpolator.Evaluate(1.4, 0.7, &f, &dfdr, nullptr);
}
