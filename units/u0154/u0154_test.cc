// FILE: u0154_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericLimitsJetRoundError, P1_SingleStatement) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  auto result = obj.round_error();
  (void)result;
}
