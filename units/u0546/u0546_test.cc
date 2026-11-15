// FILE: u0546_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
// Path P1 calls fmax(const Lhs& x, const Rhs& y).
TEST(Unitu0546, CallsTarget) {
  fmax({}, {});
}
}  // namespace ceres
