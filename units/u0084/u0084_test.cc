// FILE: u0084_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMultiplyTest, TC1_JetTimesJet) {
  Jet<double, 4> f;
  f.a = 1.5;
  f.v[0] = 0.5;
  f.v[1] = -1.0;
  f.v[2] = 2.0;
  f.v[3] = 3.5;

  Jet<double, 4> g;
  g.a = -2.0;
  g.v[0] = -0.5;
  g.v[1] = 1.0;
  g.v[2] = 4.0;
  g.v[3] = -3.0;

  Jet<double, 4> h = f * g;
  (void)h;
}

}  // namespace
}  // namespace ceres
