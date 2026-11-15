// FILE: u0157_test.cc
#include <limits>

#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (hàm không có nhánh)
TEST(JetSignalingNaNTest, P1_ReturnJetFromSignalingNaN) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  ceres::Jet<double, 2> result = obj.signaling_NaN();
  (void)result;  // Không kiểm tra kết quả trả về
}
