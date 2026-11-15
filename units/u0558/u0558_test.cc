// FILE: u0558_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"

namespace ceres {
namespace internal {
// Path P1 calls StableIndependentSetOrdering(const Graph<Vertex>& graph, std::vector<Vertex>* ordering).
TEST(Unitu0558, CallsTarget) {
  double ordering_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  StableIndependentSetOrdering({}, ordering_data);
}

// Path P2 calls StableIndependentSetOrdering(const Graph<Vertex>& graph, std::vector<Vertex>* ordering) on the alternate CFG path.
TEST(Unitu0558, CallsTargetAlternate) {
  double ordering_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  StableIndependentSetOrdering({}, ordering_data);
}
}  // namespace internal
}  // namespace ceres
