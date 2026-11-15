// FILE: u0637_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1 calls operator-=(const Jet<T, N> & y).
TEST(Unitu0637, CallsTarget) {
  object.operator-=({});
}
