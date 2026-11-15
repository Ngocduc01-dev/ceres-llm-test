// FILE: u0804_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"
#include "ceres/polynomial.cc"

// P1: START -> 1 -> END
TEST(RemoveLeadingZerosTest, TC1_CallsTarget) {
  Vector & polynomial_in a0{};
  RemoveLeadingZeros(a0);
}

// P2: START -> 1 -> END
TEST(RemoveLeadingZerosTest, TC2_CallsTarget) {
  Vector & polynomial_in a0{};
  RemoveLeadingZeros(a0);
}

