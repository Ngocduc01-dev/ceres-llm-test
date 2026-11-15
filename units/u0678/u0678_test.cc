// FILE: u0678_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"

// Path P1 calls VertexDegreeLessThan(const Graph<Vertex> & graph).
TEST(Unitu0678, CallsTarget) {
  object.VertexDegreeLessThan({});
}
