// FILE: u0556_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0556, CallsTarget) {
  Degree2MaximumSpanningForest({});
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0556, CallsTargetAlternate) {
  Degree2MaximumSpanningForest({});
}
}  // namespace internal
}  // namespace ceres
