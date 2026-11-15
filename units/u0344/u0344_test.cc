// FILE: u0344_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

#include <random>

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionManifoldMinus, SinglePath) {
  ceres::QuaternionManifold manifold;

  // Seed cố định để giá trị luôn giống nhau giữa các lần chạy.
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-1.0, 1.0);

  double x[4];
  double y[4];
  for (int i = 0; i < 4; ++i) {
    x[i] = dist(gen);
    y[i] = dist(gen);
  }
  double y_minus_x[3] = {0.0, 0.0, 0.0};

  // Không kiểm tra kết quả trả về, chỉ gọi hàm để đi qua node 1.
  manifold.Minus(y, x, y_minus_x);
}
