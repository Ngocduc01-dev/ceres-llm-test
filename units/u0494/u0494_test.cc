// FILE: u0494_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

TEST(Unit_u0494, EvaluatesValueAndDerivative) {
  Eigen::Matrix<double, 1, 1> p0;
  Eigen::Matrix<double, 1, 1> p1;
  Eigen::Matrix<double, 1, 1> p2;
  Eigen::Matrix<double, 1, 1> p3;
  p0 << 0.0;
  p1 << 1.0;
  p2 << 2.0;
  p3 << 3.0;
  double value[1] = {};
  double derivative[1] = {};

  ceres::CubicHermiteSpline<1>(
      p0, p1, p2, p3, 0.5, value, derivative);

  EXPECT_DOUBLE_EQ(value[0], 1.5);
  EXPECT_DOUBLE_EQ(derivative[0], 1.0);
}
