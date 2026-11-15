// FILE: u0807_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"
#include "ceres/polynomial.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0807, TC1_CallsTarget) {
  Vector polynomial{};
  ceres::internal::(anonymous)::FindLinearPolynomialRoots(polynomial, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0807, TC2_CallsTarget) {
  Vector polynomial{};
  ceres::internal::(anonymous)::FindLinearPolynomialRoots(polynomial, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0807, TC3_CallsTarget) {
  Vector polynomial{};
  ceres::internal::(anonymous)::FindLinearPolynomialRoots(polynomial, nullptr, nullptr);
}
