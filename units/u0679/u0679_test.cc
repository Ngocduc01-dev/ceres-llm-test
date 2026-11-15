// FILE: u0679_test.cc
#include "gtest/gtest.h"
#include "ceres/graph_algorithms.h"

// Path P1 calls operator()(const Vertex & lhs, const Vertex & rhs) const.
TEST(Unitu0679, CallsTarget) {
  object.operator({});
}
