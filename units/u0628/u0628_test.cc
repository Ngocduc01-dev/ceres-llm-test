// FILE: u0628_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1 calls FixedArray(std::initializer_list<value_type> init_list, const allocator_type & a).
TEST(Unitu0628, CallsTarget) {
  object.FixedArray({}, {});
}
