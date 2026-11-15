// FILE: u0309_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(GraphVerticesTest, P1_ReturnVertices) {
  Graph<int> graph;
  const auto& vertices = graph.vertices();
  (void)vertices;
}

}  // namespace internal
}  // namespace ceres
