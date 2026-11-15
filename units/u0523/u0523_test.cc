// FILE: u0523_test.cc
#include "gtest/gtest.h"
#include "ceres/casts.h"

namespace ceres {
// Path P1 calls down_cast(foo).
TEST(Unitu0523, CallsTarget) {
  down_cast({});
}
}  // namespace ceres
