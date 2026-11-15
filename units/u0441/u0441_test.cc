// FILE: u0441_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0441, PathP1) {
  double arg_0 = 1.0;
  double arg_1 = 1.0;
  double * arg_2 = nullptr;
  double * arg_3 = nullptr;
  double * arg_4 = nullptr;
  ceres::BiCubicInterpolator<Grid2D<double>> target(arg_0, arg_1, arg_2, arg_3, arg_4);
  target.Evaluate(1.0, 1.0, nullptr, nullptr, nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0441, PathP2) {
  double arg_0 = 1.0;
  double arg_1 = 1.0;
  double * arg_2 = nullptr;
  double * arg_3 = nullptr;
  double * arg_4 = nullptr;
  ceres::BiCubicInterpolator<Grid2D<double>> target(arg_0, arg_1, arg_2, arg_3, arg_4);
  target.Evaluate(1.0, 1.0, nullptr, nullptr, nullptr);
}
