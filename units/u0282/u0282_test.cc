// FILE: u0282_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0282, PathP1) {
  ceres::TrustRegionStrategy::Options options;
  ceres::internal::DoglegStrategy object(options);
  object.StepIsInvalid();
}
