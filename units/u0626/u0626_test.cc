// FILE: u0626_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1 calls FixedArray(const FixedArray<T, N, A> & other, const allocator_type & a).
TEST(Unitu0626, CallsTarget) {
  object.FixedArray({}, {});
}
