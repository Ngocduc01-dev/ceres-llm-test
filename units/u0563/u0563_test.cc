// FILE: u0563_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1 calls AsValueType(pointer ptr).
TEST(Unitu0563, CallsTarget) {
  object.AsValueType(1);
}
