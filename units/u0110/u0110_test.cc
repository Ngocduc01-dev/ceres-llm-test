// FILE: u0110_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetAsin, SinglePath) {
  Jet<double, 2> f;
  f.a = 0.37;
  f.v[0] = 0.52;
  f.v[1] = -0.81;
  Jet<double, 2> r = asin(f);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
