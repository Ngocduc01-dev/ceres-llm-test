// FILE: u1027_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1027, TC1_CallsTarget) {
  size_type i{};
  ceres::internal::FixedArray object{};
  object(i);
}
