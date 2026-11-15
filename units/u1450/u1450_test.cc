// FILE: u1450_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1450, TC1_CallsTarget) {
  Vector x{};
  Vector gradient{};
  const double cost{};
  ceres::internal::TrustRegionMinimizer object{};
  object.DoLineSearch(x, gradient, cost, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1450, TC2_CallsTarget) {
  Vector x{};
  Vector gradient{};
  const double cost{};
  ceres::internal::TrustRegionMinimizer object{};
  object.DoLineSearch(x, gradient, cost, nullptr);
}
