// FILE: u0069_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetConstructorValueTest, P1_ConstructFromValue) {
  const double value = 2.5;
  ceres::Jet<double, 4> jet(value);
  (void)jet;
}
