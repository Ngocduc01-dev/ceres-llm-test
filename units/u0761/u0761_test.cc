// FILE: u0761_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

// P1: START -> 1 -> END
TEST(AddEdgeTest, TC1_CallsTarget) {
  WeightedGraph object{};
  Vertex & vertex1 a0{};
  Vertex & vertex2 a1{};
  double a2 = 0.0;
  object.AddEdge(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(AddEdgeTest, TC2_CallsTarget) {
  WeightedGraph object{};
  Vertex & vertex1 a0{};
  Vertex & vertex2 a1{};
  double a2 = 0.0;
  object.AddEdge(a0, a1, a2);
}

// P3: START -> 1 -> END
TEST(AddEdgeTest, TC3_CallsTarget) {
  WeightedGraph object{};
  Vertex & vertex1 a0{};
  Vertex & vertex2 a1{};
  double a2 = 0.0;
  object.AddEdge(a0, a1, a2);
}

