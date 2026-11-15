// FILE: u0212_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionToRotationRowMajor, P1_SinglePath) {
  const double q[4] = {0.5, 0.5, 0.5, 0.5};
  double R[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  ceres::QuaternionToRotation<double>(q, R);
}
