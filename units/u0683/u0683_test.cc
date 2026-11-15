// FILE: u0683_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_operator.h"

// Path P1 calls RightMultiplyAndAccumulate(const Vector & x, Vector & y) const.
TEST(Unitu0683, CallsTarget) {
  object.RightMultiplyAndAccumulate({}, {});
}
