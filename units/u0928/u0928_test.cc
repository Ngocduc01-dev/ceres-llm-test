// FILE: u0928_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"
#include "ceres/levenberg_marquardt_strategy.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  TrustRegionStrategy object{};
  Options & options a0{};
  object.Create(a0);
}

