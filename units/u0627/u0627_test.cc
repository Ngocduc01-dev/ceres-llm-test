// FILE: u0627_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1 calls FixedArray(FixedArray<T, N, A> && other, const allocator_type & a).
TEST(Unitu0627, CallsTarget) {
  object.FixedArray({}, {});
}
