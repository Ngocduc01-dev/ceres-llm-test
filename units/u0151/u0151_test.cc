// FILE: u0151_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(NumericLimitsJetMin, P1_ReturnJetFromMin) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  ceres::Jet<double, 2> result = (obj.min)();
  (void)result;  // Không kiểm tra kết quả trả về
}
