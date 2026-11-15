// FILE: u0731_test.cc
#include "gtest/gtest.h"

namespace ceres {
// Path P1 calls TrustRegionStrategyTypeToString(TrustRegionStrategyType type).
TEST(Unitu0731, CallsTarget) {
  TrustRegionStrategyTypeToString({});
}
}  // namespace ceres
