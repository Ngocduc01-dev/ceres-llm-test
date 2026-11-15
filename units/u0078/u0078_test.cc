// FILE: u0078_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorPlusTest, AddTwoJets) {
  Jet<double, 4> f;
  f.a = 3.0;
  f.v[0] = 1.0;
  f.v[1] = -2.0;
  f.v[2] = 4.0;
  f.v[3] = 0.5;

  Jet<double, 4> g;
  g.a = -7.0;
  g.v[0] = 2.0;
  g.v[1] = 5.0;
  g.v[2] = -3.0;
  g.v[3] = 8.0;

  Jet<double, 4> h = operator+(f, g);
  (void)h;
}

}  // namespace ceres
