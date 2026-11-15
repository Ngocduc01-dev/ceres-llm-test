// FILE: u0159_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (hàm không có nhánh rẽ)
TEST(NumericLimitsJetMax, P1_ReturnMaxJet) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  // Dùng dấu ngoặc để tránh macro max trên Windows.
  ceres::Jet<double, 2> result = (obj.max)();
  (void)result;  // Không kiểm tra kết quả trả về.
}
