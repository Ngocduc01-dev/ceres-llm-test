// FILE: u0120_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có nhánh rẽ)
TEST(Log2JetTest, P1_NoBranch) {
  ceres::Jet<double, 2> f;
  f.a = 3.7;
  f.v[0] = 1.3;
  f.v[1] = -2.4;

  ceres::Jet<double, 2> r = ceres::log2(f);
  (void)r;  // Không kiểm tra kết quả trả về
}
