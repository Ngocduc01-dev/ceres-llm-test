// FILE: u0716_test.cc
#include "gtest/gtest.h"
#include "ceres/graph_algorithms.h"

// Path P1 calls operator()(const Vertex & lhs, const Vertex & rhs) const.
TEST(Unitu0716, CallsTarget) {
  object.operator({});
}
