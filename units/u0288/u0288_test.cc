// FILE: u0288_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// Path P1: START -> END
TEST(DoglegStrategySubspaceBTest, P1_ReturnSubspaceB) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  Matrix b = strategy.subspace_B();
  (void)b;
}

}  // namespace internal
}  // namespace ceres
