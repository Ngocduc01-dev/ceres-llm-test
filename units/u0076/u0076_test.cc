// FILE: u0076_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetUnaryPlusTest, P1_ReturnsArgument) {
  Jet<double, 2> f;
  f.a = 3.0;
  f.v[0] = 1.0;
  f.v[1] = -2.0;

  const Jet<double, 2>& r = +f;
  (void)r;
}

}  // namespace internal
}  // namespace ceres
