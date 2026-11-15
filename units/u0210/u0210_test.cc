// FILE: u0210_test.cc
#include <random>

#include "ceres/rotation.h"
#include "gtest/gtest.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EulerAnglesToRotationMatrixRowStride, SinglePath) {
  std::mt19937 gen(12345);
  std::uniform_real_distribution<double> dist(-180.0, 180.0);

  double euler[3];
  for (int i = 0; i < 3; ++i) {
    euler[i] = dist(gen);
  }
  double R[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  ceres::EulerAnglesToRotationMatrix<double>(euler, 3, R);
}
