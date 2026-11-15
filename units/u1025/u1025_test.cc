// FILE: u1025_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1025, TC1_CallsTarget) {
  size_type n{};
  allocator_type a{};
  FixedArray<int, 20> object{};
  (void)object;
}
