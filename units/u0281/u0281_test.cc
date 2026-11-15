// FILE: u0281_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END
TEST(DoglegStrategyStepRejected, TC1_P1_SingleStatementPath) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  strategy.StepRejected(0.25);
}

}  // namespace internal
}  // namespace ceres
