// FILE: u0150_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có nhánh)
TEST(JetPowDoubleExponent, P1_StraightLine) {
  Jet<double, 2> f(2.7, 0);  // a = 2.7, v = (1, 0)
  f.v[0] = 1.0;
  f.v[1] = 0.5;
  const double g = 1.8;

  Jet<double, 2> r = pow(f, g);
  (void)r;  // không kiểm tra kết quả
}

}  // namespace internal
}  // namespace ceres
