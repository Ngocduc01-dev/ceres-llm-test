// FILE: u0081_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMinus, TC1_BinarySubtraction) {
  using JetT = ceres::Jet<double, 4>;

  JetT f;
  f.a = 3.0;
  f.v[0] = 1.0;
  f.v[1] = -2.0;
  f.v[2] = 5.0;
  f.v[3] = 7.0;

  JetT g;
  g.a = -4.0;
  g.v[0] = 6.0;
  g.v[1] = 2.0;
  g.v[2] = -3.0;
  g.v[3] = 9.0;

  JetT h = f - g;
  (void)h;
}
