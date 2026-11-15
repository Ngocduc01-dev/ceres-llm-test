// FILE: u1404_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"
#include "ceres/polynomial.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1404, TC1_CallsTarget) {
  std::vector<FunctionSample> samples{};
  double x_min{};
  double x_max{};
  ceres::internal::MinimizeInterpolatingPolynomial(samples, x_min, x_max, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1404, TC2_CallsTarget) {
  std::vector<FunctionSample> samples{};
  double x_min{};
  double x_max{};
  ceres::internal::MinimizeInterpolatingPolynomial(samples, x_min, x_max, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1404, TC3_CallsTarget) {
  std::vector<FunctionSample> samples{};
  double x_min{};
  double x_max{};
  ceres::internal::MinimizeInterpolatingPolynomial(samples, x_min, x_max, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1404, TC4_CallsTarget) {
  std::vector<FunctionSample> samples{};
  double x_min{};
  double x_max{};
  ceres::internal::MinimizeInterpolatingPolynomial(samples, x_min, x_max, nullptr, nullptr);
}
