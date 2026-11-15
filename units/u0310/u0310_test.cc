// FILE: u0310_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(WeightedGraphVerticesTest, P1_ReturnVerticesOfDefaultGraph) {
  ceres::internal::WeightedGraph<int> graph;
  const auto& vertices = graph.vertices();
  (void)vertices;
}
