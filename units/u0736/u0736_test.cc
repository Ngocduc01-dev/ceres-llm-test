// FILE: u0736_test.cc
#include "gtest/gtest.h"

namespace ceres {
// Path P1 calls VisibilityClusteringTypeToString(VisibilityClusteringType type).
TEST(Unitu0736, CallsTarget) {
  VisibilityClusteringTypeToString({});
}
}  // namespace ceres
