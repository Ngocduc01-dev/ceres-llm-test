// FILE: u0928_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"
#include "ceres/levenberg_marquardt_strategy.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0928, TC1_CallsTarget) {
  Options options{};
  ceres::internal::TrustRegionStrategy object{};
  object.Create(options);
}
