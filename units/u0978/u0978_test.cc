// FILE: u0978_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END
TEST(memsizeTest, TC1_CallsTarget) {
  FixedArray object{};
  object.memsize();
}

