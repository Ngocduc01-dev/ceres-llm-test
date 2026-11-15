// FILE: u0213_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DotProductTest, P1_StraightLine) {
  const double x[3] = {1.5, -2.0, 3.25};
  const double y[3] = {0.5, 4.0, -1.0};
  double result = ceres::DotProduct<double>(x, y);
  (void)result;  // Không kiểm tra kết quả trả về
}
