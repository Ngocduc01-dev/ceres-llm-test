// FILE: u0134_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsNanTest, TC1_SinglePath) {
  ceres::Jet<double, 2> f;
  f.a = 3.7;
  f.v[0] = 1.5;
  f.v[1] = -2.0;
  bool result = ceres::isnan(f);
  (void)result;  // Không kiểm tra kết quả trả về
}
