// FILE: u0126_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJ0Test, TC1_SingleStraightPath) {
  const double x = 3.7;
  double r = ceres::BesselJ0(x);
  (void)r;  // Không kiểm tra kết quả trả về
}
