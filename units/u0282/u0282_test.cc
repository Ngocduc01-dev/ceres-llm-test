// FILE: u0282_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DoglegStrategyStepIsInvalidTest, P1_TC1_StraightLine) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  strategy.StepIsInvalid();
}

}  // namespace internal
}  // namespace ceres
