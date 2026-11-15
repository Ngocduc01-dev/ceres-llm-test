// FILE: u0439_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// P1: START -> 1 -> 2(đúng) -> 3 -> 4 -> 2(đúng) -> 3 -> 4 -> 2(sai) -> END
// Phủ: node 2: đúng, node 2: sai (vòng lặp chạy đúng 2 lần, DATA_DIMENSION = 2)
TEST(CubicInterpolatorEvaluateJet, TC1_LoopTwoIterations) {
  const double data[4] = {1.0, 2.0, 3.0, 4.0};
  ceres::Grid1D<double, 2> grid(data, 0, 2);
  ceres::CubicInterpolator<ceres::Grid1D<double, 2>> interpolator(grid);

  ceres::Jet<double, 4> x(0.5, 0);
  ceres::Jet<double, 4> f[2];

  interpolator.Evaluate(x, f);
}
