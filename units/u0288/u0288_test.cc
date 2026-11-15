// FILE: u0288_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

TEST(Unit_u0288, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::TrustRegionStrategy::Options options;
  ceres::internal::DoglegStrategy object(options);
  object.subspace_B();
}
