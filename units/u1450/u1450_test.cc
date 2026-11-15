// FILE: u1450_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(u1450_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.DoLineSearch(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1450_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.DoLineSearch(nullptr, nullptr, nullptr, nullptr);
}
