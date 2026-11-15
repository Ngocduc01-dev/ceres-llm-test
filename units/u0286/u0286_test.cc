// FILE: u0286_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(DoglegStrategySubspaceBasisTest, P1_ReturnsSubspaceBasis) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  Matrix basis = strategy.subspace_basis();
  (void)basis;
}

}  // namespace internal
}  // namespace ceres
