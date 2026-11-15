// FILE: u0506_test.cc
#include "gtest/gtest.h"
#include "ceres/graph_algorithms.h"

namespace ceres {
namespace internal {
// Path P1 calls FindConnectedComponent(const Vertex& vertex, std::unordered_map<Vertex, Vertex>* union_find).
TEST(Unitu0506, CallsTarget) {
  double union_find_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  FindConnectedComponent({}, union_find_data);
}
}  // namespace internal
}  // namespace ceres
