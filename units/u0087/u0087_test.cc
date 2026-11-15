// FILE: u0087_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetDivisionTest, P1_StraightLine) {
  using J = ceres::Jet<double, 5>;

  J f;
  f.a = 7.0;
  f.v[0] = 2.0;
  f.v[1] = 9.0;
  f.v[2] = 4.0;
  f.v[3] = 6.0;
  f.v[4] = 1.0;

  J g;
  g.a = 3.0;
  g.v[0] = 5.0;
  g.v[1] = 8.0;
  g.v[2] = 3.0;
  g.v[3] = 10.0;
  g.v[4] = 7.0;

  J h = f / g;
  (void)h;
}
