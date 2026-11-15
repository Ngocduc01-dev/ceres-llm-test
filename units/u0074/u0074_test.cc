// FILE: u0074_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMulAssignScalarTest, P1_MultiplyAssignByScalar) {
  ceres::Jet<double, 2> a(3.0, 0);
  const double s = 2.0;
  a *= s;
}
