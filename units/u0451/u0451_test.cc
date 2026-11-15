// FILE: u0451_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: node 1: đúng (g.a == 0) -> node 2 -> END
TEST(JetCopysignCft, GaIsZero) {
  Jet<double, 2> f(2.5);
  f.v[0] = 1.5;
  f.v[1] = -3.0;
  Jet<double, 2> g(0.0);
  g.v[0] = 4.0;
  g.v[1] = 0.5;
  Jet<double, 2> r = ceres::copysign(f, g);
  (void)r;
}

// Path P2: node 1: sai (g.a != 0) -> node 2 -> END
TEST(JetCopysignCft, GaIsNonZero) {
  Jet<double, 2> f(3.25);
  f.v[0] = -2.0;
  f.v[1] = 1.0;
  Jet<double, 2> g(-1.75);
  g.v[0] = 0.75;
  g.v[1] = 2.5;
  Jet<double, 2> r = ceres::copysign(f, g);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
