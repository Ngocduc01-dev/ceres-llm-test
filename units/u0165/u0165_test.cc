// FILE: u0165_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumTraitsJetLowest, StraightLinePath) {
  using JetType = ceres::Jet<double, 2>;
  Eigen::NumTraits<JetType> obj;
  JetType result = obj.lowest();
  (void)result;  // Không kiểm tra kết quả trả về
}
