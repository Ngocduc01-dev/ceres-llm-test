// FILE: u0211_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionToScaledRotationTest, TC1_P1_SinglePath) {
  const double q[4] = {0.5, -0.25, 0.75, 0.125};
  double R[3 * 3] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  ceres::QuaternionToScaledRotation<double>(q, R);
}
