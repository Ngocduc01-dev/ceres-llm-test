// FILE: u0807_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"
#include "ceres/polynomial.cc"

// P1: START -> 1 -> END
TEST(FindLinearPolynomialRootsTest, TC1_CallsTarget) {
  Vector & polynomial a0{};
  FindLinearPolynomialRoots(a0, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(FindLinearPolynomialRootsTest, TC2_CallsTarget) {
  Vector & polynomial a0{};
  FindLinearPolynomialRoots(a0, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(FindLinearPolynomialRootsTest, TC3_CallsTarget) {
  Vector & polynomial a0{};
  FindLinearPolynomialRoots(a0, nullptr, nullptr);
}

