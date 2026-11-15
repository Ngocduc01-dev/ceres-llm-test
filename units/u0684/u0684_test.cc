// FILE: u0684_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_operator.h"

// Path P1 calls LeftMultiplyAndAccumulate(const Vector & x, Vector & y) const.
TEST(Unitu0684, CallsTarget) {
  object.LeftMultiplyAndAccumulate({}, {});
}
