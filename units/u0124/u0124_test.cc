// FILE: u0124_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetErfTest, SinglePathNoBranch) {
  using JetType = ceres::Jet<double, 2>;
  JetType x(0.37);
  x.v[0] = 0.52;
  x.v[1] = -0.81;
  JetType result = erf(x);
  (void)result;
}
