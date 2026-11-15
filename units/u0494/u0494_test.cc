// FILE: u0494_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// P1: node 2: đúng, node 4: đúng
TEST(CubicHermiteSplineTest, BothOutputsNonNull) {
  Eigen::Matrix<double, 1, 1> p0;
  Eigen::Matrix<double, 1, 1> p1;
  Eigen::Matrix<double, 1, 1> p2;
  Eigen::Matrix<double, 1, 1> p3;
  p0 << 1.3;
  p1 << -2.1;
  p2 << 0.7;
  p3 << 3.4;
  const double x = 0.6;
  double f = 0.0;
  double dfdx = 0.0;
  ceres::CubicHermiteSpline<1>(p0, p1, p2, p3, x, &f, &dfdx);
}

// P2: node 2: sai, node 4: sai
TEST(CubicHermiteSplineTest, BothOutputsNull) {
  Eigen::Matrix<double, 1, 1> p0;
  Eigen::Matrix<double, 1, 1> p1;
  Eigen::Matrix<double, 1, 1> p2;
  Eigen::Matrix<double, 1, 1> p3;
  p0 << -4.2;
  p1 << 2.5;
  p2 << 1.1;
  p3 << -0.9;
  const double x = 0.25;
  ceres::CubicHermiteSpline<1>(p0, p1, p2, p3, x, nullptr, nullptr);
}
