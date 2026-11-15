// FILE: u1314_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

// P1: START -> 1 -> END
TEST(u1314_Test, TC1_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.FindMinimumOnTrustRegionBoundary(nullptr);
}

// P2: START -> 1 -> END
TEST(u1314_Test, TC2_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.FindMinimumOnTrustRegionBoundary(nullptr);
}

// P3: START -> 1 -> END
TEST(u1314_Test, TC3_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.FindMinimumOnTrustRegionBoundary(nullptr);
}

// P4: START -> 1 -> END
TEST(u1314_Test, TC4_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.FindMinimumOnTrustRegionBoundary(nullptr);
}
