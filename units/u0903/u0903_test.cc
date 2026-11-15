// FILE: u0903_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0903, TC1_CallsTarget) {
  ceres::internal::TrustRegionStrategy object{};
  object.~TrustRegionStrategy();
}
