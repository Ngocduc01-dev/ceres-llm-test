// FILE: u0127_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJ1Test, TC1_SinglePath) {
  const double x = 3.7;
  double result = ceres::BesselJ1(x);
  (void)result;  // Không kiểm tra kết quả trả về
}
