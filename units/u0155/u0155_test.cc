// FILE: u0155_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericLimitsJetInfinity, TC1_P1_DoubleN2) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  ceres::Jet<double, 2> result = obj.infinity();
  (void)result;  // Không kiểm tra kết quả trả về
}
