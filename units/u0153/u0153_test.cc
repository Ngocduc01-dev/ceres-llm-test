// FILE: u0153_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericLimitsJetEpsilon, TC1_P1_Epsilon) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  auto result = obj.epsilon();
  static_cast<void>(result);
}
