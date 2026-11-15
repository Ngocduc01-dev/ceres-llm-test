// FILE: u0494_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0494, PathP1) {
  const Eigen::Matrix<double, kDataDimension, 1>& arg_0{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_1{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_2{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_3{}
  ceres::CubicHermiteSpline<double>(arg_0, arg_1, arg_2, arg_3, 1.0, nullptr, nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0494, PathP2) {
  const Eigen::Matrix<double, kDataDimension, 1>& arg_0{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_1{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_2{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_3{}
  ceres::CubicHermiteSpline<double>(arg_0, arg_1, arg_2, arg_3, 1.0, nullptr, nullptr);
}

// Path P3: START -> 1 -> END.
TEST(Unit_u0494, PathP3) {
  const Eigen::Matrix<double, kDataDimension, 1>& arg_0{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_1{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_2{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_3{}
  ceres::CubicHermiteSpline<double>(arg_0, arg_1, arg_2, arg_3, 1.0, nullptr, nullptr);
}

// Path P4: START -> 1 -> END.
TEST(Unit_u0494, PathP4) {
  const Eigen::Matrix<double, kDataDimension, 1>& arg_0{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_1{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_2{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_3{}
  ceres::CubicHermiteSpline<double>(arg_0, arg_1, arg_2, arg_3, 1.0, nullptr, nullptr);
}
