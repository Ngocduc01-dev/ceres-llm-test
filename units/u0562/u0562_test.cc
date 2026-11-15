// FILE: u0562_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1 calls DefaultConstructorIsNonTrivial().
TEST(Unitu0562, CallsTarget) {
  object.DefaultConstructorIsNonTrivial();
}
