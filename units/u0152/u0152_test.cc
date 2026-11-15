// FILE: u0152_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericLimitsJetLowestTest, TC1_P1_LowestDoubleN2) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  ceres::Jet<double, 2> result = obj.lowest();
  (void)result;  // Không kiểm tra kết quả trả về
}
