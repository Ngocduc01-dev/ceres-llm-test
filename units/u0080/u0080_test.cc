// FILE: u0080_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorPlusScalarLeft, SinglePath) {
  Jet<double, 4> f;
  f.a = -2.0;
  f.v[0] = 1.5;
  f.v[1] = -4.0;
  f.v[2] = 0.5;
  f.v[3] = 7.0;

  const double s = 3.5;
  Jet<double, 4> r = s + f;
  (void)r;
}

}  // namespace internal
}  // namespace ceres
