// FILE: u0551_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
// Path P1 calls pow(T f, const Jet<T, N>& g).
TEST(Unitu0551, CallsTarget) {
  pow({}, {});
}
}  // namespace ceres
