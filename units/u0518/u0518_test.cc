// FILE: u0518_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
// Path P1 calls fdim(const Lhs& f, const Rhs& g).
TEST(Unitu0518, CallsTarget) {
  fdim({}, {});
}
}  // namespace ceres
