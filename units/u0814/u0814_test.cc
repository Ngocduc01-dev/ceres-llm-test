// FILE: u0814_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"
#include "ceres/polynomial.cc"

// P1: START -> 1 -> END
TEST(FindQuadraticPolynomialRootsTest, TC1_CallsTarget) {
  Vector & polynomial a0{};
  FindQuadraticPolynomialRoots(a0, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(FindQuadraticPolynomialRootsTest, TC2_CallsTarget) {
  Vector & polynomial a0{};
  FindQuadraticPolynomialRoots(a0, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(FindQuadraticPolynomialRootsTest, TC3_CallsTarget) {
  Vector & polynomial a0{};
  FindQuadraticPolynomialRoots(a0, nullptr, nullptr);
}

