// FILE: u0778_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"
#include "ceres/function_sample.h"

// P1: START -> 1 -> END
TEST(FindInterpolatingPolynomialTest, TC1_CallsTarget) {
  std::vector<FunctionSample> & samples a0{};
  ceres::internal::FindInterpolatingPolynomial(a0);
}

// P2: START -> 1 -> END
TEST(FindInterpolatingPolynomialTest, TC2_CallsTarget) {
  std::vector<FunctionSample> & samples a0{};
  ceres::internal::FindInterpolatingPolynomial(a0);
}

// P3: START -> 1 -> END
TEST(FindInterpolatingPolynomialTest, TC3_CallsTarget) {
  std::vector<FunctionSample> & samples a0{};
  ceres::internal::FindInterpolatingPolynomial(a0);
}

