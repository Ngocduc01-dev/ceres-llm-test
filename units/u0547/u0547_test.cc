// FILE: u0547_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
// Path P1 calls fmin(const Lhs& x, const Rhs& y).
TEST(Unitu0547, CallsTarget) {
  fmin({}, {});
}
}  // namespace ceres
