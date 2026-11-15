// FILE: u1129_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"

// P1: START -> 1 -> END
TEST(FindPolynomialRootsTest, TC1_CallsTarget) {
  Vector & polynomial_in a0{};
  ceres::internal::FindPolynomialRoots(a0, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(FindPolynomialRootsTest, TC2_CallsTarget) {
  Vector & polynomial_in a0{};
  ceres::internal::FindPolynomialRoots(a0, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(FindPolynomialRootsTest, TC3_CallsTarget) {
  Vector & polynomial_in a0{};
  ceres::internal::FindPolynomialRoots(a0, nullptr, nullptr);
}

