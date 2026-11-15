// FILE: u0100_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetAbsTest, TC1_P1_NoBranch) {
  Jet<double, 2> f;
  f.a = -3.0;
  f.v[0] = 1.5;
  f.v[1] = -2.0;

  Jet<double, 2> r = abs(f);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
