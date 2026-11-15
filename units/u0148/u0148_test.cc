// FILE: u0148_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetAtan2Test, TC1_SingleStraightPath) {
  using JetT = Jet<double, 8>;

  JetT f;
  JetT g;
  f.a = 3.0;
  g.a = 2.0;

  const double fv[8] = {1.0, -2.0, 3.0, 0.5, -1.5, 4.0, -3.0, 2.0};
  const double gv[8] = {-1.0, 2.0, 0.5, 3.0, -4.0, 1.0, 2.5, -0.5};
  for (int i = 0; i < 8; ++i) {
    f.v[i] = fv[i];
    g.v[i] = gv[i];
  }

  JetT result = atan2(g, f);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
