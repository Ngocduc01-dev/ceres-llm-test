// FILE: u0075_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetDivideAssignScalar, TC1_P1_Node1) {
  ceres::Jet<double, 2> a(4.0, 0);
  const double s = 3.0;
  a /= s;
}
