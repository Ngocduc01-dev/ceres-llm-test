// FILE: u0804_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"
#include "ceres/polynomial.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0804, TC1_CallsTarget) {
  Vector polynomial_in{};
  ceres::internal::(anonymous)::RemoveLeadingZeros(polynomial_in);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0804, TC2_CallsTarget) {
  Vector polynomial_in{};
  ceres::internal::(anonymous)::RemoveLeadingZeros(polynomial_in);
}
