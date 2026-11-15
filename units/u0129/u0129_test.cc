// FILE: u0129_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJ0JetTest, TC1_SinglePath) {
  using JetT = ceres::Jet<double, 2>;
  JetT f(2.5, 0);
  JetT r = ceres::BesselJ0(f);
  (void)r;  // Không kiểm tra kết quả trả về
}
