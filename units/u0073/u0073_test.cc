// FILE: u0073_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMinusAssignScalarTest, TC1_P1_SinglePath) {
  ceres::Jet<double, 2> a(3.5, 0);
  const double s = 1.25;
  a -= s;
}
