// FILE: u0752_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"

// P1: START -> 1 -> END
TEST(DifferentiatePolynomialTest, TC1_CallsTarget) {
  Vector & polynomial a0{};
  ceres::internal::DifferentiatePolynomial(a0);
}

// P2: START -> 1 -> END
TEST(DifferentiatePolynomialTest, TC2_CallsTarget) {
  Vector & polynomial a0{};
  ceres::internal::DifferentiatePolynomial(a0);
}

// P3: START -> 1 -> END
TEST(DifferentiatePolynomialTest, TC3_CallsTarget) {
  Vector & polynomial a0{};
  ceres::internal::DifferentiatePolynomial(a0);
}

