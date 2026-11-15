// FILE: u0158_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericLimitsJetDenormMin, P1_StraightLine) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  auto result = obj.denorm_min();
  (void)result;
}
