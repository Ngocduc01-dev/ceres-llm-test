// FILE: u0163_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumTraitsJetMaxDigits10, P1_SingleStatement) {
  Eigen::NumTraits<ceres::Jet<double, 2>> obj;
  int result = obj.max_digits10();
  (void)result;  // Không kiểm tra kết quả trả về
}
