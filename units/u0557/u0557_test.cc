// FILE: u0557_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0557, CallsTarget) {
  double ordering_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  IndependentSetOrdering({}, ordering_data);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0557, CallsTargetAlternate) {
  double ordering_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  IndependentSetOrdering({}, ordering_data);
}
}  // namespace internal
}  // namespace ceres
