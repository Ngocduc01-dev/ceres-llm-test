// FILE: u0156_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

#include <limits>

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(NumericLimitsJetQuietNaN, P1_LinearPath) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  ceres::Jet<double, 2> result = obj.quiet_NaN();
  (void)result;  // Không kiểm tra kết quả trả về
}
