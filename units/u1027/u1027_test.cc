// FILE: u1027_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END
TEST(operator[]Test, TC1_CallsTarget) {
  FixedArray object{};
  size_type a0{};
  object.operator[](a0);
}

