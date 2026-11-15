// FILE: u0761_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0761, TC1_CallsTarget) {
  Vertex vertex1{};
  Vertex vertex2{};
  double weight{};
  ceres::internal::WeightedGraph object{};
  object.AddEdge(vertex1, vertex2, weight);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0761, TC2_CallsTarget) {
  Vertex vertex1{};
  Vertex vertex2{};
  double weight{};
  ceres::internal::WeightedGraph object{};
  object.AddEdge(vertex1, vertex2, weight);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0761, TC3_CallsTarget) {
  Vertex vertex1{};
  Vertex vertex2{};
  double weight{};
  ceres::internal::WeightedGraph object{};
  object.AddEdge(vertex1, vertex2, weight);
}
