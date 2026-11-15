// FILE: u0624_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/array_selector.h"
#include "ceres/internal/fixed_array.h"

// Path P1 calls ArraySelector(int s).
TEST(Unitu0624, CallsTarget) {
  object.ArraySelector(1);
}
