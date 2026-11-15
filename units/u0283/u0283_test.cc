// FILE: u0283_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DoglegStrategyRadiusTest, TC1_ReturnRadius) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  strategy.Radius();
}

}  // namespace internal
}  // namespace ceres
