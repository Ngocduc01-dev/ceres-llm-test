// FILE: u0636_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1 calls operator+=(const Jet<T, N> & y).
TEST(Unitu0636, CallsTarget) {
  object.operator+=({});
}
