// FILE: u0088_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorDivScalarByJet, P1_StraightLine) {
  const double s = 3.5;
  Jet<double, 4> g;
  g.a = 2.0;
  g.v[0] = 1.0;
  g.v[1] = 2.0;
  g.v[2] = 3.0;
  g.v[3] = 4.0;

  Jet<double, 4> result = operator/(s, g);
  (void)result;
}

}  // namespace
}  // namespace ceres
