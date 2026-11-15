// FILE: u0184_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

#include <random>

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldMinusJacobianTest, P1_StraightLine) {
  // Seed cố định để mỗi lần chạy cho cùng một giá trị.
  std::mt19937 gen(12345);
  std::uniform_int_distribution<int> size_dist(1, 5);
  const int size = size_dist(gen);

  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(size);

  double x[5] = {0.5, -1.2, 2.0, 0.3, -0.7};
  double jacobian[25] = {0.0};

  // Không kiểm tra kết quả trả về (không có kết quả đúng để so).
  manifold.MinusJacobian(x, jacobian);
}
