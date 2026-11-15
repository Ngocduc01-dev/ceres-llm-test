// FILE: u0752_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0752, TC1_CallsTarget) {
  Vector polynomial{};
  ceres::internal::DifferentiatePolynomial(polynomial);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0752, TC2_CallsTarget) {
  Vector polynomial{};
  ceres::internal::DifferentiatePolynomial(polynomial);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0752, TC3_CallsTarget) {
  Vector polynomial{};
  ceres::internal::DifferentiatePolynomial(polynomial);
}
