// FILE: u0564_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1 calls UsingInlinedStorage(size_type n).
TEST(Unitu0564, CallsTarget) {
  object.UsingInlinedStorage(1);
}
