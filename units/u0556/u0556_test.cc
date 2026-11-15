// FILE: u0556_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"

namespace ceres {
namespace internal {
// Path P1 calls Degree2MaximumSpanningForest(const WeightedGraph<Vertex>& graph).
TEST(Unitu0556, CallsTarget) {
  Degree2MaximumSpanningForest({});
}

// Path P2 calls Degree2MaximumSpanningForest(const WeightedGraph<Vertex>& graph) on the alternate CFG path.
TEST(Unitu0556, CallsTargetAlternate) {
  Degree2MaximumSpanningForest({});
}
}  // namespace internal
}  // namespace ceres
