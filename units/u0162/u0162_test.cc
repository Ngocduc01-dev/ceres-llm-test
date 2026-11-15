// FILE: u0162_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumTraitsJetDigits10, SinglePath) {
  using JetType = ceres::Jet<double, 2>;
  Eigen::NumTraits<JetType> obj;
  int result = obj.digits10();
  (void)result;  // không kiểm tra kết quả trả về
}
