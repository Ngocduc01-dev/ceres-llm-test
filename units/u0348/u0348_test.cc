// FILE: u0348_test.cc
#include <cmath>
#include <random>

#include "ceres/manifold.h"
#include "gtest/gtest.h"

namespace ceres {

namespace {

// Sinh quaternion Eigen (thứ tự x, y, z, w) ngẫu nhiên đã chuẩn hoá.
void MakeUnitQuaternion(std::mt19937& gen, double* q) {
  std::uniform_real_distribution<double> dist(-1.0, 1.0);
  double norm = 0.0;
  for (int i = 0; i < 4; ++i) {
    q[i] = dist(gen);
    norm += q[i] * q[i];
  }
  norm = std::sqrt(norm);
  if (norm < 1e-3) {
    q[0] = 0.0;
    q[1] = 0.0;
    q[2] = 0.0;
    q[3] = 1.0;
    return;
  }
  for (int i = 0; i < 4; ++i) {
    q[i] /= norm;
  }
}

}  // namespace

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(EigenQuaternionManifoldMinus, StraightLinePath) {
  std::mt19937 gen(42);
  double y[4];
  double x[4];
  double y_minus_x[3] = {0.0, 0.0, 0.0};
  MakeUnitQuaternion(gen, y);
  MakeUnitQuaternion(gen, x);

  EigenQuaternionManifold manifold;
  manifold.Minus(y, x, y_minus_x);
}

}  // namespace ceres
