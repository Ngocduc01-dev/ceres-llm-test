// FILE: u0284_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
TEST(DoglegStrategyGradientTest, P1_StartToEnd) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  Vector g = strategy.gradient();
  (void)g;
}

}  // namespace internal
}  // namespace ceres
