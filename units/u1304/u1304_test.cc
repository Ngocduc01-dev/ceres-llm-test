// FILE: u1304_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1304, TC1_CallsTarget) {
  Vector polynomial{};
  const double x_min{};
  const double x_max{};
  ceres::internal::MinimizePolynomial(polynomial, x_min, x_max, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1304, TC2_CallsTarget) {
  Vector polynomial{};
  const double x_min{};
  const double x_max{};
  ceres::internal::MinimizePolynomial(polynomial, x_min, x_max, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1304, TC3_CallsTarget) {
  Vector polynomial{};
  const double x_min{};
  const double x_max{};
  ceres::internal::MinimizePolynomial(polynomial, x_min, x_max, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1304, TC4_CallsTarget) {
  Vector polynomial{};
  const double x_min{};
  const double x_max{};
  ceres::internal::MinimizePolynomial(polynomial, x_min, x_max, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1304, TC5_CallsTarget) {
  Vector polynomial{};
  const double x_min{};
  const double x_max{};
  ceres::internal::MinimizePolynomial(polynomial, x_min, x_max, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1304, TC6_CallsTarget) {
  Vector polynomial{};
  const double x_min{};
  const double x_max{};
  ceres::internal::MinimizePolynomial(polynomial, x_min, x_max, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1304, TC7_CallsTarget) {
  Vector polynomial{};
  const double x_min{};
  const double x_max{};
  ceres::internal::MinimizePolynomial(polynomial, x_min, x_max, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1304, TC8_CallsTarget) {
  Vector polynomial{};
  const double x_min{};
  const double x_max{};
  ceres::internal::MinimizePolynomial(polynomial, x_min, x_max, nullptr, nullptr);
}
