// FILE: u0786_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0786, TC1_CallsTarget) {
  ceres::internal::FixedArray object{};
  object.AsValueType(nullptr);
}
