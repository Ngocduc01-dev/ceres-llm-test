// FILE: u0079_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorPlusScalarRight, P1_SingleStatement) {
  Jet<double, 4> f;
  f.a = 3.5;
  f.v[0] = 1.25;
  f.v[1] = -2.0;
  f.v[2] = 4.5;
  f.v[3] = 0.75;
  const double s = -6.25;

  Jet<double, 4> r = operator+(f, s);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
