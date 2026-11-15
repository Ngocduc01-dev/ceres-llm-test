// FILE: u0555_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
// Path P1 calls pow(const Jet<T, N>& f, const Jet<T, N>& g).
TEST(Unitu0555, CallsTarget) {
  pow({}, {});
}
}  // namespace ceres
